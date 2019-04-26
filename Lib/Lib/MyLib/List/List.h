#pragma once
#include "../etc/Define.h"
#include "../etc/Vector2.h"

class List
{
public:
	// �R���X�g���N�^
	List(const D3D12_COMMAND_LIST_TYPE& type);
	// �f�X�g���N�^
	~List();

	// ���Z�b�g
	void Reset(ID3D12PipelineState* pipe = nullptr) const;

	// �r���[�|�[�g�Z�b�g
	void Viewport(const Vec2& size) const;

	// �V�U�[�Z�b�g
	void Scissor(const Vec2& size) const;

	// �o���A�Z�b�g
	void Barrier(const D3D12_RESOURCE_STATES& befor, const D3D12_RESOURCE_STATES& affter, ID3D12Resource* rsc) const;

	// ���[�g�V�O�l�`���Z�b�g
	void SetRoot(std::weak_ptr<Root>root) const;

	// �p�C�v���C���̃Z�b�g
	void SetPipe(std::weak_ptr<Pipe>pipe) const;

	// �q�[�v�Z�b�g
	void SetHeap(ID3D12DescriptorHeap** heap, const size_t& num) const;

	// ���[�g�ƃq�[�v�̊֘A�t��
	void GraphicTable(const unsigned int& id, ID3D12DescriptorHeap* heap, const unsigned int& index) const;

	// ���_�o�b�t�@�r���[�Z�b�g
	void VertexView(const D3D12_VERTEX_BUFFER_VIEW& view) const;

	// �C���f�b�N�X�o�b�t�@�r���[�Z�b�g
	void IndexView(const D3D12_INDEX_BUFFER_VIEW& view) const;

	// �g�|���W�[�Z�b�g
	void Topology(const D3D_PRIMITIVE_TOPOLOGY& type) const;

	// ���_�`��
	void DrawVertex(const size_t& num, const unsigned int& instance = 1) const;

	// �o���h�����s
	void Bundle(List* list) const;

	// ���X�g����
	void Close(void) const;

	// �A���P�[�^�擾
	ID3D12CommandAllocator* GetAllo(void) const;

	// ���X�g�擾
	ID3D12GraphicsCommandList* GetList(void) const;

private:
	List(const List&) = delete;
	void operator=(const List&) = delete;

	// �A���P�[�^����
	long CreateAllo(const D3D12_COMMAND_LIST_TYPE& type);

	// ���X�g����
	long CreateList(const D3D12_COMMAND_LIST_TYPE& type);


	// �A���P�[�^
	ID3D12CommandAllocator* allo;

	// ���X�g
	ID3D12GraphicsCommandList* list;
};
