#pragma once
#include "../etc/Define.h"
#include "../etc/Func.h"
#include "../etc/Vector2.h"
#include "../etc/Vector3.h"
#include <vector>

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

public:
	Texture(const std::string& filePath);
	~Texture();

	// �ǂݍ���
	int Load(const std::string& filePath);

	// �`��
	void Draw(std::weak_ptr<List> list);

	// �摜�T�C�Y�擾
	Vec2 GetTexSize()const;

	// �摜�̍��W
	Vec2f pos;

private:
	// �萔���\�[�X����
	long CreateCB(const unsigned int index);

	// ���_���\�[�X����
	long CreateVB(const unsigned int index);

	// �T�u���\�[�X��������
	long WriteSubResource(const std::string& path, const size_t& index);

	// �`�揀��
	unsigned int SetDraw(std::weak_ptr<List> list, std::weak_ptr<Root> root, std::weak_ptr<Pipe> pipe);

	void ChangePos(std::vector<Vertex>& vert);

	std::vector<Vertex> vert;
	ID3D12DescriptorHeap* heap;
	std::vector<ID3D12Resource*> rsc;

	unsigned int vbIndex;
};