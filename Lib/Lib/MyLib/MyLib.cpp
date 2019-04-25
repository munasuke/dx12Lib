#include "MyLib.h"
#include "Window/Window.h"
#include "List/List.h"
#include "Queue/Queue.h"
#include "Fence/Fence.h"
#include "Root/Root.h"
#include "Pipe/Pipe.h"
#include <d3d12.h>

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

	RootSignature("tex", { "MyLib/Shader/Texture/TexVS.hlsl", "MyLib/Shader/Texture/TexPS.hlsl" });
	PipeLine("tex", "tex", D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, { 0, 1 }, false);
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
}

// 実行
void MyLib::Execution(void) const
{
}
