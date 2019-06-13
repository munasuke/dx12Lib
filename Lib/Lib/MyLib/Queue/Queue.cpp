#include "Queue.h"
#include "../etc/Func.h"
#include "../etc/Release.h"

// コンストラクタ
Queue::Queue(const D3D12_COMMAND_LIST_TYPE& type) :
	queue(nullptr)
{
	CreateQueue(type);
}

// デストラクタ
Queue::~Queue()
{
	Release(queue);
}

// キュー生成
long Queue::CreateQueue(const D3D12_COMMAND_LIST_TYPE& type)
{
	D3D12_COMMAND_QUEUE_DESC desc{};
	desc.Type = type;

	auto hr = Dev->CreateCommandQueue(&desc, IID_PPV_ARGS(&queue));
	if (FAILED(hr))
	{
		func::DebugLog("キュー生成：失敗");
	}

	return hr;
}

// 実行
void Queue::Execution(ID3D12CommandList** list, const size_t& num) const
{
	queue->ExecuteCommandLists(unsigned int(num), list);
}

//キュー取得
ID3D12CommandQueue* Queue::Get() const
{
	return queue;
}
