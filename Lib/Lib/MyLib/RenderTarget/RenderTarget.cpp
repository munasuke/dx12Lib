#include "RenderTarget.h"
#include "../SwapChain/SwapChain.h"
#include "../List/List.h"
#include "../Descriptor/Descriptor.h"
#include "../etc/Release.h"
#include "../etc/Func.h"
#include <dxgi1_6.h>

const float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };

RenderTarget::RenderTarget(std::weak_ptr<SwapChain> swap) :
	swap(swap), heap(nullptr)
{
	CreateRenderTarget();
}

RenderTarget::~RenderTarget()
{
	for(auto& rt : rsc)
	{
		Release(rt);
	}
	Release(heap);
}

void RenderTarget::Clear(std::weak_ptr<List> list)
{
	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += Dev->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * swap.lock()->Get()->GetCurrentBackBufferIndex();

	list.lock()->GetList()->OMSetRenderTargets(1, &handle, 0, nullptr);
	list.lock()->GetList()->ClearRenderTargetView(handle, color, 0, nullptr);
}

long RenderTarget::CreateRenderTarget()
{
	DXGI_SWAP_CHAIN_DESC1 dsc{};
	swap.lock()->Get()->GetDesc1(&dsc);
	rsc.resize(dsc.BufferCount);

	auto hr = Descriptor::Get().CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
		D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_NONE, rsc.size());
	if (FAILED(hr))
	{
		return S_FALSE;
	}

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	for (int i = 0; i < rsc.size(); ++i)
	{
		hr = swap.lock()->Get()->GetBuffer(i, IID_PPV_ARGS(&rsc[i]));
		Descriptor::Get().RTV(*rsc[i], *heap, i);
	}

	return hr;
}

ID3D12Resource* RenderTarget::GetRsc() const
{
	return rsc[swap.lock()->Get()->GetCurrentBackBufferIndex()];
}
