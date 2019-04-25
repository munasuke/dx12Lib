#include "Fence.h"
#include "../Queue/Queue.h"
#include "../etc/Func.h"
#include "../etc/Release.h"

// コンストラクタ
Fence::Fence(std::weak_ptr<Queue>queue) : queue(queue),
fence(nullptr), handle(CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS)), cnt(0)
{
	CreateFence();
}

// デストラクタ
Fence::~Fence()
{
	Release(fence);
	CloseHandle(handle);
}

// フェンス生成
long Fence::CreateFence(void)
{
	auto hr = Dev->CreateFence(cnt, D3D12_FENCE_FLAGS::D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	if (FAILED(hr))
	{
		func::DebugLog("フェンス生成：失敗");
		return hr;
	}

	cnt = 1;

	return hr;
}

// 待機
void Fence::Wait(void)
{
	//フェンス値更新
	++cnt;

	//フェンス値を変更
	auto hr = queue.lock()->Get()->Signal(fence, cnt);
	if (FAILED(hr))
	{
		func::DebugLog("フェンス値更新：失敗");
		return;
	}

	//完了を待機(ポーリング)
	while (fence->GetCompletedValue() != cnt)
	{
		//フェンスイベントのセット
		hr = fence->SetEventOnCompletion(cnt, handle);
		if (FAILED(hr))
		{
			func::DebugLog("フェンスイベントセット：失敗");
			return;
		}

		//フェンスイベントの待機
		WaitForSingleObject(handle, INFINITE);
	}
}