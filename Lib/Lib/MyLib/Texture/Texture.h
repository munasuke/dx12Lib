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

	// �萔
	struct Constant
	{
		// �s��
		DirectX::XMFLOAT4X4 matrix;

		// uv���W
		Vec2f uvPos;

		// uv�T�C�Y
		Vec2f uvSize;

		// ���]
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

	// �ǂݍ���
	int Load(const std::string& filePath);

	void Delete(const std::string& filePath);

	// �`��
	void Draw(std::weak_ptr<List> list);

	// �摜�T�C�Y�擾
	Vec2f GetTexSize(const std::string& filePath)const;

	// �摜�̍��W
	Vec2f pos;

	// �摜�̃T�C�Y
	Vec2f size;

	// �摜�̕����n�_�̍�����W
	Vec2f offsetPos;

	// �摜�̕����T�C�Y
	Vec2f divSize;

	void operator=(const Texture& tex);
private:
	// ������
	int Init();

	// �萔���\�[�X����
	long CreateCB(const unsigned int index);
	long CreateCB2(const unsigned int index);

	// ���_���\�[�X����
	long CreateVB(const unsigned int index);

	// �T�u���\�[�X��������
	long WriteSubResource(const std::string& path, const size_t& index);

	// �`�揀��
	unsigned int SetDraw(std::weak_ptr<List> list, std::weak_ptr<Root> root, std::weak_ptr<Pipe> pipe);

	// ���_
	std::vector<Vertex> vert;

	// �q�[�v
	ID3D12DescriptorHeap* heap;

	// ���\�[�X
	std::vector<ID3D12Resource*> rsc;

	// �萔�f�[�^
	Constant* con;

	// ���_�f�[�^
	void* data;

	// �摜�̉�]
	float rotate;

	// �摜�̔��]
	Vec2f reverse;

	// �t�@�C���p�X
	std::string filePath;

	ConstantData* cData;
	ID3D12Resource* cRsc;
};