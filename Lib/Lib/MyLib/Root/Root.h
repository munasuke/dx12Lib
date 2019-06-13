#pragma once
#include "../etc/Define.h"
#include <string>

class Root
{
public:
	// �R���X�g���N�^
	Root();
	// �f�X�g���N�^
	~Root();

	// ���_�V�F�[�_�R���p�C��
	void Vertex(const std::string& fileName, const std::string& func, const std::string& ver);

	// �s�N�Z���V�F�[�_�R���p�C��
	void Pixel(const std::string& fileName, const std::string& func, const std::string& ver);

	// .cso�ǂݍ���
	void Vertex(const std::string& fileName);
	void Pixel(const std::string& fileName);

	void Vertex(const int& id);
	void Pixel(const int& id);

	// ���[�g�擾
	ID3D12RootSignature* Get() const;
	// ���_�V�F�[�_�擾
	ID3DBlob* Vertex() const;
	// �s�N�Z���V�F�[�_�擾
	ID3DBlob* Pixel() const;

private:
	Root(const Root&) = delete;
	void operator=(const Root&) = delete;

	// �V�F�[�_�R���p�C��
	long Compile(const std::string& fileName, const std::string& func, const std::string& ver, ID3DBlob** blob);

	// .cso�ǂݍ���
	long Load(const std::string& fileName, ID3DBlob** blob);

	// ���\�[�X�ǂݍ���
	long Read(const int& id, ID3DBlob** blob);

	// ���[�g���擾
	long RootInfo(ID3DBlob* blob);

	// ���[�g�V�O�l�`������
	long CreateRoot();


	// ���[�g
	ID3D12RootSignature* root;

	// �V�O�l�`��
	ID3DBlob* sig;

	// ���_�V�F�[�_
	ID3DBlob* vertex;

	// �s�N�Z���V�F�[�_
	ID3DBlob* pixel;
};
