#include "Descriptor.h"
#include "../Device/Device.h"
#include <d3d12.h>

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

long Descriptor::CreateHeap(ID3D12DescriptorHeap ** heap, const D3D12_DESCRIPTOR_HEAP_TYPE & type, 
	const D3D12_DESCRIPTOR_HEAP_FLAGS & flag, const size_t & descriptorNum)
{
	D3D12_DESCRIPTOR_HEAP_DESC dsc{};
	dsc.Flags          = flag;
	dsc.NodeMask       = 0;
	dsc.NumDescriptors = unsigned int(descriptorNum);
	dsc.Type           = type;

	auto hr = Device::Get().GetDev()->CreateDescriptorHeap(&dsc, IID_PPV_ARGS(&(*heap)));

#ifdef _DEBUG
	if (FAILED(hr))
	{
		OutputDebugStringA("\nヒープ生成：失敗\n");
	}
#endif

	return hr;
}

long Descriptor::CreateRsc(ID3D12Resource ** rsc, const D3D12_HEAP_PROPERTIES & hprop, D3D12_RESOURCE_DESC & dsc, 
	const D3D12_RESOURCE_STATES & state, const D3D12_CLEAR_VALUE * clear)
{
	auto hr = Device::Get().GetDev()->CreateCommittedResource(&hprop, D3D12_HEAP_FLAGS::D3D12_HEAP_FLAG_NONE,
		&dsc, state, clear, IID_PPV_ARGS(&(*rsc)));

#ifdef _DEBUG
	if (FAILED(hr))
	{
		OutputDebugStringA("\nリソース生成：失敗\n");
	}
#endif

	return hr;
}

void Descriptor::RTV(ID3D12Resource & rsc, ID3D12DescriptorHeap & heap, const size_t & index)
{
	D3D12_RENDER_TARGET_VIEW_DESC dsc{};
	dsc.Format        = rsc.GetDesc().Format;
	dsc.ViewDimension = D3D12_RTV_DIMENSION::D3D12_RTV_DIMENSION_TEXTURE2D;

	auto handle = heap.GetCPUDescriptorHandleForHeapStart();
	handle.ptr += Device::Get().GetDev()->GetDescriptorHandleIncrementSize(heap.GetDesc().Type) * unsigned int(index);

	Device::Get().GetDev()->CreateRenderTargetView(&rsc, &dsc, handle);
}

void Descriptor::SRV()
{
}
