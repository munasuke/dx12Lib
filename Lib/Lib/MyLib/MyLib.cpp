#include "MyLib.h"
#include "Window/Window.h"
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

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

// クラスのインスタンス
void MyLib::Instance(const Vec2& pos, const Vec2& size, void* parent)
{
#ifdef _DEBUG
	ID3D12Debug* debug = nullptr;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
	debug->EnableDebugLayer();
#endif

	win = std::make_shared<Window>(pos, size, parent);
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
