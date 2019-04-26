#pragma once
#include "etc/Define.h"
#include "etc/Vector3.h"
#include "Primitive/Primitive.h"
#include "Texture/Texture.h"
#include <string>
#include <unordered_map>

class MyLib
{
	// �萔
	struct Constant
	{
		Vec3f color;
		float alpha;
		Vec2f winSize;
	};

public:
	// �R���X�g���N�^
	MyLib(const Vec2& size, const Vec2& pos = 0x80000000);
	MyLib(const MyLib& lib, const Vec2& size, const Vec2& pos = 0x80000000);
	MyLib(std::weak_ptr<MyLib>lib, const Vec2& size, const Vec2& pos = 0x80000000);
	// �f�X�g���N�^
	~MyLib();

	// �^�C�g�����ύX
	void ChangeTitle(const std::string& title) const;

	// �E�B���h�E���W�擾
	Vec2 GetWinPos(void) const;

	// �E�B���h�E�T�C�Y�擾
	Vec2 GetWinSize(void) const;

	// ���b�Z�[�W�m�F
	bool CheckMsg(void) const;

	// ��ʃN���A
	void Clear(void) const;

	// �v���~�e�B�u�`��
	void Draw(Primitive& prim);

	// �摜�`��
	void Draw(Texture& tex);

	// ���s
	void Execution(void) const;

private:
	MyLib(const MyLib&) = delete;
	void operator=(const MyLib&) = delete;

	//	���[�g�̃C���X�^���X
	void RootSignature(const std::string& name, const std::initializer_list<std::string>& fileName);

	// �p�C�v�̃C���X�^���X
	void PipeLine(const std::string& name, const std::string& rootName,
		const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const std::initializer_list<unsigned int>& index, const bool& depth);


	// �N���X�̃C���X�^���X
	void Instance(const Vec2& pos, const Vec2& size, void* parent);

	// ������
	void Init();

	// �E�B���h�E
	std::shared_ptr<Window>win;

	// ���X�g
	std::shared_ptr<List>list;

	// �L���[
	std::shared_ptr<Queue>queue;

	// �t�F���X
	std::unique_ptr<Fence>fence;

	// �X���b�v�`�F�C��
	std::shared_ptr<SwapChain> swap;

	// �����_�[�^�[�Q�b�g
	std::unique_ptr<RenderTarget> rt;

	// ���[�g
	static std::unordered_map<std::string, std::shared_ptr<Root>>root;

	// �p�C�v
	static std::unordered_map<std::string, std::shared_ptr<Pipe>>pipe;
	
	// �q�[�v
	ID3D12DescriptorHeap* heap;

	// ���\�[�X
	ID3D12Resource* rsc;

	// �萔�f�[�^
	Constant* constant;
};
