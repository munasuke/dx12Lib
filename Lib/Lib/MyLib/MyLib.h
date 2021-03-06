#pragma once
#include "etc/Define.h"
#include "etc/Vector3.h"
#include "Primitive/Primitive.h"
#include "Texture/Texture.h"
#include "Input/Input.h"
#include <string>
#include <unordered_map>

class MyLib
{
	// 定数
	struct Constant
	{
		Vec3f color;
		float alpha;
		Vec2f winSize;
	};

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
	Vec2 GetWinPos() const;

	// ウィンドウサイズ取得
	Vec2 GetWinSize() const;

	// カーソル座標取得
	Vec2 GetMousePos()const;

	// カーソルクライアント座標取得
	Vec2 GetMousePosClient()const;

	// メッセージ確認
	bool CheckMsg() const;

	// 画面クリア
	void Clear() const;

	// プリミティブ描画
	void Draw(Primitive& prim, const Vec3f& color, const float alpha = 1.0f);

	// 画像描画
	void Draw(Texture& tex, const float alpha = 1.0f, const bool turnX = false, const bool turnY = false);

	// 実行
	void Execution() const;

private:
	MyLib(const MyLib&) = delete;
	void operator=(const MyLib&) = delete;

	//	ルートのインスタンス
	template<typename T>
	void RootSignature(const std::string& name, const std::initializer_list<T>& fileName);

	// パイプのインスタンス
	void PipeLine(const std::string& name, const std::string& rootName,
		const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const std::initializer_list<unsigned int>& index, const bool& depth);


	// クラスのインスタンス
	void Instance(const Vec2& pos, const Vec2& size, void* parent);

	// 初期化
	void Init();

	// リソース生成
	void CreateRes();

	// ウィンドウ
	std::shared_ptr<Window>win;

	// リスト
	std::shared_ptr<List>list;

	// キュー
	std::shared_ptr<Queue>queue;

	// フェンス
	std::unique_ptr<Fence>fence;

	// スワップチェイン
	std::shared_ptr<SwapChain> swap;

	// レンダーターゲット
	std::unique_ptr<RenderTarget> rt;

	// ルート
	static std::unordered_map<std::string, std::shared_ptr<Root>>root;

	// パイプ
	static std::unordered_map<std::string, std::shared_ptr<Pipe>>pipe;
	
	// ヒープ
	ID3D12DescriptorHeap* heap;

	// リソース
	ID3D12Resource* rsc;

	// 定数データ
	Constant* constant;

	// winSize
	Vec2f winSize;
};
