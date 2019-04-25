#include "Descriptor.h"
#include "../etc/Func.h"
#include "../etc/Release.h"

Descriptor::Descriptor()
{
}

Descriptor::~Descriptor()
{
}

Descriptor & Descriptor::Get()
{
	static Descriptor instance;
	return instance;
}

long Descriptor::CreateHeap(ID3D12DescriptorHeap** heap, const D3D12_DESCRIPTOR_HEAP_TYPE& type, 
	const D3D12_DESCRIPTOR_HEAP_FLAGS& flag, const size_t& descriptorNum)
{
	D3D12_DESCRIPTOR_HEAP_DESC dsc{};
	dsc.Flags          = flag;
	dsc.NodeMask       = 0;
	dsc.NumDescriptors = unsigned int(descriptorNum);
	dsc.Type           = type;

	auto hr = Dev->CreateDescriptorHeap(&dsc, IID_PPV_ARGS(&(*heap)));
	if (FAILED(hr))
	{
		func::DebugLog("ヒープ生成：失敗");
	}

	return hr;
}

long Descriptor::CreateRsc(ID3D12Resource** rsc, const D3D12_HEAP_PROPERTIES& hprop, D3D12_RESOURCE_DESC& dsc, 
	const D3D12_RESOURCE_STATES& state, const D3D12_CLEAR_VALUE* clear)
{
	auto hr = Dev->CreateCommittedResource(&hprop, D3D12_HEAP_FLAGS::D3D12_HEAP_FLAG_NONE, &dsc, state, clear, IID_PPV_ARGS(&(*rsc)));
	if (FAILED(hr))
	{
		func::DebugLog("リソース生成：失敗");
	}

	return hr;
}

void Descriptor::RTV(ID3D12Resource& rsc, ID3D12DescriptorHeap& heap, const size_t& index)
{
	D3D12_RENDER_TARGET_VIEW_DESC dsc{};
	dsc.Format        = rsc.GetDesc().Format;
	dsc.ViewDimension = D3D12_RTV_DIMENSION::D3D12_RTV_DIMENSION_TEXTURE2D;

	auto handle = heap.GetCPUDescriptorHandleForHeapStart();
	handle.ptr += Dev->GetDescriptorHandleIncrementSize(heap.GetDesc().Type) * unsigned int(index);

	Dev->CreateRenderTargetView(&rsc, &dsc, handle);
}

void Descriptor::SRV()
{
}
