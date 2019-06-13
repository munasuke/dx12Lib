#include "MyLib.h"
#include "Window/Window.h"
#include "List/List.h"
#include "Queue/Queue.h"
#include "Fence/Fence.h"
#include "Root/Root.h"
#include "Pipe/Pipe.h"
#include "SwapChain/SwapChain.h"
#include "RenderTarget/RenderTarget.h"
#include "etc/Release.h"
#include "../resource.h"
#include <DirectXMath.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

std::unordered_map<std::string, std::shared_ptr<Root>> MyLib::root;
std::unordered_map<std::string, std::shared_ptr<Pipe>> MyLib::pipe;

// インプット一覧
const D3D12_INPUT_ELEMENT_DESC inputs[] = {
	//0
	{ "POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	//2
	{ "TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,       0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
};

// コンストラクタ
MyLib::MyLib(const Vec2& size, const Vec2& pos)
{
	CoInitializeEx(nullptr, COINIT::COINIT_APARTMENTTHREADED);

#ifdef _DEBUG
	ID3D12Debug* debug = nullptr;
	auto hr = D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
	debug->EnableDebugLayer();
#endif

	Init();

	winSize = Vec2f(float(size.x), float(size.y));
	//constant->winSize = Vec2f(float(size.x), float(size.y));

	Instance(pos, size, nullptr);
}

// コンストラクタ
MyLib::MyLib(const MyLib& lib, const Vec2& size, const Vec2& pos)
{
	Init();

	winSize = Vec2f(float(size.x), float(size.y));
	//constant->winSize = Vec2f(float(size.x), float(size.y));

	Instance(pos, size, lib.win->Get());
}

// コンストラクタ
MyLib::MyLib(std::weak_ptr<MyLib>lib, const Vec2& size, const Vec2& pos)
{
	Init();

	winSize = Vec2f(float(size.x), float(size.y));
	//constant->winSize = Vec2f(float(size.x), float(size.y));

	Instance(pos, size, lib.lock()->win->Get());
}

// デストラクタ
MyLib::~MyLib()
{
	Desc.UnMap(rsc);
	Release(rsc);
	Release(heap);
}

//	ルートのインスタンス
template<typename T>
void MyLib::RootSignature(const std::string& name, const std::initializer_list<T>& fileName)
{
	if (root.find(name) != root.end())
	{
		return;
	}
	root[name] = std::make_shared<Root>();
	auto itr = fileName.begin();
	while (itr != fileName.end())
	{
		//root[name]->Vertex(*itr, "main", "vs_5_1");
		root[name]->Vertex(*itr);
		++itr;
		//root[name]->Pixel(*itr, "main", "ps_5_1");
		root[name]->Pixel(*itr);
		++itr;
	}
}
template void MyLib::RootSignature(const std::string& name, const std::initializer_list<int>& fileName);
template void MyLib::RootSignature(const std::string& name, const std::initializer_list<std::string>& fileName);

// パイプのインスタンス
void MyLib::PipeLine(const std::string& name, const std::string& rootName, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const std::initializer_list<unsigned int>& index, const bool& depth)
{
	if (pipe.find(name) != pipe.end())
	{
		return;
	}

	std::vector<D3D12_INPUT_ELEMENT_DESC>input;
	for (auto& i : index)
	{
		input.push_back(inputs[i]);
	}

	pipe[name] = std::make_shared<Pipe>(root[rootName], *input.data(), input.size(), type, depth);
}

// クラスのインスタンス
void MyLib::Instance(const Vec2& pos, const Vec2& size, void* parent)
{
	win   = std::make_shared<Window>(pos, size, parent);
	list  = std::make_shared<List>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	queue = std::make_shared<Queue>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	fence = std::make_unique<Fence>(queue);
	swap  = std::make_shared<SwapChain>(win, queue);
	rt    = std::make_unique<RenderTarget>(swap);

	//RootSignature("prim", { "MyLib/Shader/Primitive/PrimVS.hlsl", "MyLib/Shader/Primitive/PrimPS.hlsl" });
	//RootSignature("prim", { "Shader/PrimVS.cso", "Shader/PrimPS.cso" });
	RootSignature("prim", { PRIM_VS, PRIM_PS });
	PipeLine("point",    "prim", D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT,    { 0 }, false);
	PipeLine("line",     "prim", D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE,     { 0 }, false);
	PipeLine("triangle", "prim", D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, { 0 }, false);

	//RootSignature("tex", { "MyLib/Shader/Texture/TexVS.hlsl", "MyLib/Shader/Texture/TexPS.hlsl" });
	//RootSignature("tex", { "Shader/TexVS.cso", "Shader/TexPS.cso" });
	RootSignature("tex", { TEX_VS, TEX_PS });
	PipeLine("tex", "tex", D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, { 0, 1 }, false);
}

// 初期化
void MyLib::Init()
{
	heap     = nullptr;
	rsc      = nullptr;
	constant = nullptr;

	//CreateRes();
}

// リソース生成
void MyLib::CreateRes()
{
	Desc.CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
		D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);

	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE;
	desc.Format           = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = (sizeof(Constant) + 0xff) &~0xff;

	Desc.CreateRsc(&rsc, prop, desc, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);

	Desc.CBV(rsc, heap);

	Desc.Map(rsc, (void**)(&constant));
}

// タイトル名変更
void MyLib::ChangeTitle(const std::string& title) const
{
	SetWindowTextA(HWND(win->Get()), title.c_str());
}

// ウィンドウ座標取得
Vec2 MyLib::GetWinPos() const
{
	RECT rect{};
	GetWindowRect(HWND(win->Get()), &rect);
	return Vec2(int(rect.left), int(rect.top));
}

// ウィンドウサイズ取得
Vec2 MyLib::GetWinSize() const
{
	RECT rect{};
	GetClientRect(HWND(win->Get()), &rect);
	return Vec2(int(rect.right), int(rect.bottom));
}

// カーソル座標取得
Vec2 MyLib::GetMousePos() const
{
	POINT point{};
	GetCursorPos(&point);
	return Vec2(int(point.x), int(point.y));
}

// カーソルクライアント座標取得
Vec2 MyLib::GetMousePosClient() const
{
	POINT point{};
	point.x = long(GetMousePos().x);
	point.y = long(GetMousePos().y);

	ScreenToClient(HWND(win->Get()), &point);

	return Vec2(int(point.x), int(point.y));
}

// メッセージ確認
bool MyLib::CheckMsg() const
{
	static MSG msg{};

	if (msg.message == WM_QUIT)
	{
		return false;
	}

	//呼び出し側スレッドが所有しているウィンドウに送信されたメッセージの保留されている物を取得
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		//仮想キーメッセージを文字メッセージに変換
		TranslateMessage(&msg);
		//1つのウィドウプロシージャにメッセージを送出する
		DispatchMessage(&msg);
	}

	return true;
}

// 画面クリア
void MyLib::Clear() const
{
	list->Reset();

	list->Viewport(GetWinSize());
	list->Scissor(GetWinSize());

	list->Barrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET, rt->GetRsc());

	rt->Clear(list);
}

// プリミティブ描画
void MyLib::Draw(Primitive& prim, const Vec3f& color, const float alpha)
{
	prim.UpData();
	list->SetRoot(root["prim"]);
	switch (prim.type)
	{
	case 0:
		break;
	case 1:
		list->SetPipe(pipe["point"]);
		break;
	case 2:
		list->SetPipe(pipe["line"]);
		break;
	default:
		list->SetPipe(pipe["triangle"]);
		break;
	}

	//constant->alpha = alpha;
	//constant->color = color;
	prim.cData->color = { color.x, color.y, color.z, alpha };
	prim.cData->winSize = { float(GetWinSize().x), float(GetWinSize().y) };

	D3D12_VERTEX_BUFFER_VIEW view{};
	view.BufferLocation = prim.rsc->GetGPUVirtualAddress();
	view.SizeInBytes    = unsigned int(prim.rsc->GetDesc().Width);
	view.StrideInBytes  = sizeof(prim.pos[0]);
	list->VertexView(view);

	list->SetHeap(&prim.heap, 1);
	list->GraphicTable(0, prim.heap, 0);

	list->Topology(D3D12_PRIMITIVE_TOPOLOGY(prim.type));

	list->DrawVertex(prim.pos.size());
}

// 画像描画
void MyLib::Draw(Texture& tex, const float alpha, const bool turnX, const bool turnY)
{
	tex.cData->alpha   = alpha;
	tex.cData->winSize = Vec2f(float(GetWinSize().x), float(GetWinSize().y));

	tex.vert[0] = { Vec3f(0.0f, 0.0f),                        Vec2f(0.0f, 0.0f) };
	tex.vert[1] = { Vec3f(Vec2f(tex.cData->winSize.x, 0.0f)), Vec2f(1.0f, 0.0f) };
	tex.vert[2] = { Vec3f(Vec2f(0.0f, tex.cData->winSize.y)), Vec2f(0.0f, 1.0f) };
	tex.vert[3] = { Vec3f(tex.cData->winSize),                Vec2f(1.0f) };

	memcpy(tex.data, tex.vert.data(), sizeof(tex.vert[0]) * tex.vert.size());

	//constant->alpha = alpha;
	tex.reverse = Vec2f(turnX ? 1.0f : 0.0f, turnY ? 1.0f : 0.0f);

	DirectX::XMStoreFloat4x4(&tex.con->matrix, DirectX::XMMatrixAffineTransformation2D(
		DirectX::XMLoadFloat2(&Convert2(tex.size / tex.cData->winSize)),
		DirectX::XMLoadFloat2(&Convert2(tex.size / 2.0f)),
		tex.rotate,
		DirectX::XMLoadFloat3(&Convert3(tex.pos))
	));


	tex.SetDraw(list, root["tex"], pipe["tex"]);
	//list->GraphicTable(index, tex.heap, index);

	tex.Draw(list);
}

// 実行
void MyLib::Execution() const
{
	list->Barrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, rt->GetRsc());

	list->Close();

	ID3D12CommandList* lists[] = { list->GetList() };
	queue->Execution(lists, _countof(lists));

	swap->Present();

	fence->Wait();
}
