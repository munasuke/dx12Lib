#include "Queue.h"
#include "../etc/Func.h"
#include "../etc/Release.h"

// �R���X�g���N�^
Queue::Queue(const D3D12_COMMAND_LIST_TYPE& type) :
	queue(nullptr)
{
	CreateQueue(type);
}

// �f�X�g���N�^
Queue::~Queue()
{
	Release(queue);
}

// �L���[����
long Queue::CreateQueue(const D3D12_COMMAND_LIST_TYPE& type)
{
	D3D12_COMMAND_QUEUE_DESC desc{};
	desc.Type = type;

	auto hr = Dev->CreateCommandQueue(&desc, IID_PPV_ARGS(&queue));
	if (FAILED(hr))
	{
		func::DebugLog("�L���[�����F���s");
	}

	return hr;
}

// ���s
void Queue::Execution(ID3D12CommandList** list, const size_t& num) const
{
	queue->ExecuteCommandLists(unsigned int(num), list);
}

//�L���[�擾
ID3D12CommandQueue* Queue::Get() const
{
	return queue;
}
