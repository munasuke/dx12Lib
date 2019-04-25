#pragma once
#include "../etc/Vector2.h"

class Window
{
public:
	// コンストラクタ
	Window(const Vec2& pos, const Vec2& size, void* parent);
	// デストラクタ
	~Window();

	// ウィンドウハンドル取得
	void* Get(void) const;

private:
	Window(const Window&) = delete;
	void operator=(const Window&) = delete;

	// ウィンドウコールバック
#ifdef _WIN64
	static __int64 __stdcall WindowProc(void* hWnd, unsigned int message, unsigned __int64 wParam, __int64 lParam);
#else
	static long __stdcall WindowProc(void* hWnd, unsigned int message, unsigned int wParam, long lParam);
#endif

	// 初期化
	void Init(void);

	// ウィンドウ生成
	int CreateWnd(const Vec2& pos, const Vec2& size, void* parent);


	// ウィンドウハンドル
	void* handle;

	// ウィンドウインスタンス
	void* instance;

	// ウィンドウ名
	const wchar_t* name;
};
