#pragma once
#include "etc/Define.h"
#include "etc/Vector2.h"
#include <string>

class MyLib
{
public:
	// コンストラクタ
	MyLib(const Vec2& size, const Vec2& pos = 0x80000000);
	MyLib(const MyLib& lib, const Vec2& size, const Vec2& pos = 0x80000000);
	MyLib(std::weak_ptr<MyLib>lib, const Vec2& size, const Vec2& pos = 0x80000000);
	// デストラクタ
	~MyLib();

	// タイトル名変更
	void ChangeTitle(const std::string& title) const;

	// ウィンドウ座標取得
	Vec2 GetWinPos(void) const;

	// ウィンドウサイズ取得
	Vec2 GetWinSize(void) const;

	// メッセージ確認
	bool CheckMsg(void) const;

	// 画面クリア
	void Clear(void) const;

	// 実行
	void Execution(void) const;

private:
	MyLib(const MyLib&) = delete;
	void operator=(const MyLib&) = delete;

	// クラスのインスタンス
	void Instance(const Vec2& pos, const Vec2& size, void* parent);


	// ウィンドウ
	std::shared_ptr<Window>win;
};
