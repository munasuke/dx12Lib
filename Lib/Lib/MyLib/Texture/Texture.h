#pragma once
#include "../etc/Define.h"
#include "../etc/Func.h"
#include "../etc/Vector3.h"
#include <vector>
#include <DirectXMath.h>

class MyLib;

struct Vertex
{
	Vec3f pos;
	Vec2f uv;
	Vertex() : pos(Vec3f()), uv(Vec2f()) {};
	Vertex(const Vec3f& pos, const Vec2f& uv) : pos(pos), uv(uv) {};
};

class Texture
{
	friend MyLib;

	// 定数
	struct Constant
	{
		// 行列
		DirectX::XMFLOAT4X4 matrix;

		// uv座標
		Vec2f uvPos;

		// uvサイズ
		Vec2f uvSize;

		// 反転
		Vec2f reverse;
	};

	struct ConstantData
	{
		Vec3f color;
		float alpha;
		Vec2f winSize;
	};

public:
	Texture();
	Texture(const std::string& filePath);
	Texture(const Texture& tex);
	~Texture();

	// 読み込み
	int Load(const std::string& filePath);

	void Delete(const std::string& filePath);

	// 描画
	void Draw(std::weak_ptr<List> list);

	// 画像サイズ取得
	Vec2f GetTexSize(const std::string& filePath)const;

	// 画像の座標
	Vec2f pos;

	// 画像のサイズ
	Vec2f size;

	// 画像の分割地点の左上座標
	Vec2f offsetPos;

	// 画像の分割サイズ
	Vec2f divSize;

	void operator=(const Texture& tex);
private:
	// 初期化
	int Init();

	// 定数リソース生成
	long CreateCB(const unsigned int index);
	long CreateCB2(const unsigned int index);

	// 頂点リソース生成
	long CreateVB(const unsigned int index);

	// サブリソース書き込み
	long WriteSubResource(const std::string& path, const size_t& index);

	// 描画準備
	unsigned int SetDraw(std::weak_ptr<List> list, std::weak_ptr<Root> root, std::weak_ptr<Pipe> pipe);

	// 頂点
	std::vector<Vertex> vert;

	// ヒープ
	ID3D12DescriptorHeap* heap;

	// リソース
	std::vector<ID3D12Resource*> rsc;

	// 定数データ
	Constant* con;

	// 頂点データ
	void* data;

	// 画像の回転
	float rotate;

	// 画像の反転
	Vec2f reverse;

	// ファイルパス
	std::string filePath;

	ConstantData* cData;
	ID3D12Resource* cRsc;
};