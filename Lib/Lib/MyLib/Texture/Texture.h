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

	// �ǂݍ���
	int Load(const std::string& filePath);

	// ���[�g�V�O�l�`���Z�b�g
	void SetRS(std::weak_ptr<List> list, std::weak_ptr<Root> root);

	// �`�揀��
	void SetDraw(std::weak_ptr<List> list);

	// �`��
	void Draw(std::weak_ptr<List> list);

private:
	// ���_���\�[�X����
	long CreateVB(const unsigned int index);

	// �T�u���\�[�X��������
	long WriteSubResource(const std::string& path, const size_t& index);

	std::vector<Vertex> vert;
	ID3D12DescriptorHeap* heap;
	std::vector<ID3D12Resource*> rsc;

	unsigned int vbIndex;
};