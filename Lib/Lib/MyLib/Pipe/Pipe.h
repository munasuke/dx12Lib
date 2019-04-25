#pragma once
#include "../etc/Define.h"

class Pipe
{
public:
	// �R���X�g���N�^
	Pipe(std::weak_ptr<Root>root, const D3D12_INPUT_ELEMENT_DESC& input, const size_t& num, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const bool& depth);
	// �f�X�g���N�^
	~Pipe();

	// �p�C�v���C���擾
	ID3D12PipelineState* Get(void) const;

private:
	Pipe(const Pipe&) = delete;
	void operator=(const Pipe&) = delete;

	// �p�C�v���C������
	long CreatePipe(const D3D12_INPUT_ELEMENT_DESC& input, const size_t& num, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const bool& depth);


	// ���[�g
	std::weak_ptr<Root>root;

	// �p�C�v���C��
	ID3D12PipelineState* pipe;
};
