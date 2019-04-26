#pragma once
#include "../etc/Define.h"
#include "../etc/Vector3.h"
#include <vector>

class MyLib;

// �v���~�e�B�u�^�C�v
enum class PrimitiveType {
	point    = 1,
	line     = 2,
	triangle = 3,
	box      = 4
};

class Primitive
{
	friend MyLib;
public:
	// ���_�f�[�^
	std::vector<Vec3f>pos;


	// �R���X�g���N�^
	Primitive();
	Primitive(const PrimitiveType& type);
	Primitive(const PrimitiveType& type, const unsigned int& num);
	// �R�s�[�R���X�g���N�^
	Primitive(const Primitive& prim);
	// �f�X�g���N�^
	~Primitive();

	// ���Z�b�g
	void Reset(const PrimitiveType& type, const unsigned int& num);

	// ������Z�q�I�[�o�[���[�h
	void operator=(const Primitive& prim);

private:
	// ������
	void Init(void);

	// �f�[�^�X�V
	void UpData(void) const;


	// ���\�[�X
	ID3D12Resource* rsc;

	// ���M�f�[�^
	void* data;

	// �^�C�v
	int type;
};
