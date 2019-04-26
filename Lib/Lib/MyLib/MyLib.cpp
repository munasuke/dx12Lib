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
	Instance(pos, size, nullptr);
}

// コンストラクタ
MyLib::MyLib(const MyLib& lib, const Vec2& size, const Vec2& pos)
{
	Instance(pos, size, lib.win->Get());
}

// コンストラクタ
MyLib::MyLib(std::weak_ptr<MyLib>lib, const Vec2& size, const Vec2& pos)
{
	Instance(pos, size, lib.lock()->win->Get());
}

// デストラクタ
MyLib::~MyLib()
{
}

//	ルートのインスタンス
void MyLib::RootSignature(const std::string& name, const std::initializer_list<std::string>& fileName)
{
	if (root.find(name) != root.end())
	{
		return;
	}
	root[name] = std::make_shared<Root>();
	auto itr = fileName.begin();
	while (itr != fileName.end())
	{
		root[name]->Vertex(*itr, "main", "vs_5_1");
		++itr;
		root[name]->Pixel(*itr, "main", "ps_5_1");
		++itr;
	}
}

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
#ifdef _DEBUG
	ID3D12Debug* debug = nullptr;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
	debug->EnableDebugLayer();
#endif

	win   = std::make_shared<Window>(pos, size, parent);
	list  = std::make_shared<List>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	queue = std::make_shared<Queue>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	fence = std::make_unique<Fence>(queue);
	swap  = std::make_shared<SwapChain>(win, queue);
	rt    = std::make_unique<RenderTarget>(swap);

	RootSignature("prim", { "MyLib/Shader/Primitive/PrimVS.hlsl", "MyLib/Shader/Primitive/PrimPS.hlsl" });
	PipeLine("point",    "prim", D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT,    { 0 }, false);
	PipeLine("line",     "prim", D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE,     { 0 }, false);
	PipeLine("triangle", "prim", D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, { 0 }, false);

	RootSignature("tex", { "MyLib/Shader/Texture/TexVS.hlsl", "MyLib/Shader/Texture/TexPS.hlsl" });
	PipeLine("tex", "tex", D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, { 0, 1 }, false);
}

void MyLib::Init()
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
	desc.Width            = (sizeof(Constant) + 0xff) & ~0xff;

	Desc.CreateRsc(&rsc, prop, desc, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);

	Desc.CBV(*rsc, *heap);


}

// タイトル名変更
void MyLib::ChangeTitle(const std::string& title) const
{
	SetWindowTextA(HWND(win->Get()), title.c_str());
}

// ウィンドウ座標取得
Vec2 MyLib::GetWinPos(void) const
{
	RECT rect{};
	GetWindowRect(HWND(win->Get()), &rect);
	return Vec2(int(rect.left), int(rect.top));
}

// ウィンドウサイズ取得
Vec2 MyLib::GetWinSize(void) const
{
	RECT rect{};
	GetClientRect(HWND(win->Get()), &rect);
	return Vec2(int(rect.right), int(rect.bottom));
}

// メッセージ確認
bool MyLib::CheckMsg(void) const
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
void MyLib::Clear(void) const
{
	list->Reset();
	list->Viewport(GetWinSize());
	list->Scissor(GetWinSize());
	list->Barrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET, rt->GetRsc());
	rt->Clear(list);
}

// プリミティブ描画
void MyLib::Draw(Primitive& prim)
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

	D3D12_VERTEX_BUFFER_VIEW view{};
	view.BufferLocation = prim.rsc->GetGPUVirtualAddress();
	view.SizeInBytes    = unsigned int(prim.rsc->GetDesc().Width);
	view.StrideInBytes  = sizeof(prim.pos[0]);
	list->VertexView(view);

	list->Topology(D3D12_PRIMITIVE_TOPOLOGY(prim.type));

	list->DrawVertex(prim.pos.size());
}

// 画像描画
void MyLib::Draw(Texture& tex)
{
	auto index = tex.SetDraw(list, root["tex"], pipe["tex"]);


	tex.Draw(list);
}

// 実行
void MyLib::Execution(void) const
{
	list->Barrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, rt->GetRsc());

	list->Close();

	ID3D12CommandList* lists[] = { list->GetList() };
	queue->Execution(lists, _countof(lists));
	swap->Present();
	fence->Wait();
}
