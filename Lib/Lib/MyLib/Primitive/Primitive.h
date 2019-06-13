#pragma once
#include "../etc/Define.h"
#include "../etc/Vector3.h"
#include <vector>

class MyLib;

// プリミティブタイプ
enum class PrimitiveType {
	point    = 1,
	line     = 2,
	triangle = 3,
	box      = 4
};

class Primitive
{
	friend MyLib;
	struct Data
	{
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT2 winSize;
	};
public:
	// 頂点データ
	std::vector<Vec3f>pos;
	// 色
	DirectX::XMFLOAT4 color;


	// コンストラクタ
	Primitive();
	Primitive(const PrimitiveType& type);
	Primitive(const PrimitiveType& type, const unsigned int& num);
	// コピーコンストラクタ
	Primitive(const Primitive& prim);
	// デストラクタ
	~Primitive();

	// リセット
	void Reset(const PrimitiveType& type, const unsigned int& num);

	// 代入演算子オーバーロード
	void operator=(const Primitive& prim);

private:
	// 初期化
	void Init();

	// データ更新
	void UpData() const;


	// リソース
	ID3D12Resource* rsc;
	ID3D12Resource* cRsc;

	// ヒープ
	ID3D12DescriptorHeap* heap;

	// 送信データ
	void* data;
	Data* cData;

	// タイプ
	int type;
};
