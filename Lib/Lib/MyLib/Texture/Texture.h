#pragma once
#include "../etc/Define.h"
#include "../etc/Func.h"
#include "../etc/Vector2.h"
#include "../etc/Vector3.h"
#include <vector>

struct Vertex
{
	Vec3f pos;
	Vec2f uv;
	Vertex() : pos(Vec3f()), uv(Vec2f()) {};
	Vertex(const Vec3f& pos, const Vec2f& uv) : pos(pos), uv(uv) {};
};

class Texture
{
public:
	Texture(const std::string& filePath);
	~Texture();

	// 読み込み
	int Load(const std::string& filePath);

	// ルートシグネチャセット
	void SetRS(std::weak_ptr<List> list, std::weak_ptr<Root> root);

	// 描画準備
	void SetDraw(std::weak_ptr<List> list);

	// 描画
	void Draw(std::weak_ptr<List> list);

private:
	// 頂点リソース生成
	long CreateVB(const unsigned int index);

	// サブリソース書き込み
	long WriteSubResource(const std::string& path, const size_t& index);

	std::vector<Vertex> vert;
	ID3D12DescriptorHeap* heap;
	std::vector<ID3D12Resource*> rsc;

	unsigned int vbIndex;
};