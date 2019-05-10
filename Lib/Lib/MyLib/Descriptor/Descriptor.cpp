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

// ヒープ生成
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

// リソース生成
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

// RTV生成
void Descriptor::RTV(ID3D12Resource* rsc, ID3D12DescriptorHeap* heap, const size_t& index)
{
	D3D12_RENDER_TARGET_VIEW_DESC dsc{};
	dsc.Format        = rsc->GetDesc().Format;
	dsc.ViewDimension = D3D12_RTV_DIMENSION::D3D12_RTV_DIMENSION_TEXTURE2D;

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += Dev->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * unsigned int(index);

	Dev->CreateRenderTargetView(rsc, &dsc, handle);
}

// SRV生成
void Descriptor::SRV(ID3D12Resource* rsc, ID3D12DescriptorHeap* heap, const size_t& index)
{
	D3D12_SHADER_RESOURCE_VIEW_DESC dsc{};
	dsc.Format                  = rsc->GetDesc().Format;
	dsc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	dsc.Texture2D.MipLevels     = 1;
	dsc.ViewDimension           = D3D12_SRV_DIMENSION::D3D12_SRV_DIMENSION_TEXTURE2D;

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += Dev->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * unsigned int(index);

	Dev->CreateShaderResourceView(rsc, &dsc, handle);
}

// CBV生成
void Descriptor::CBV(ID3D12Resource* rsc, ID3D12DescriptorHeap* heap, const size_t& index)
{
	D3D12_CONSTANT_BUFFER_VIEW_DESC dsc{};
	dsc.BufferLocation = rsc->GetGPUVirtualAddress();
	dsc.SizeInBytes    = unsigned int(rsc->GetDesc().Width);

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += Dev->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * unsigned int(index);

	Dev->CreateConstantBufferView(&dsc, handle);
}

// DSV生成
void Descriptor::DSV(ID3D12Resource* rsc, ID3D12DescriptorHeap* heap, const size_t& index)
{
	D3D12_DEPTH_STENCIL_VIEW_DESC dsc{};
	dsc.Format        = DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;
	dsc.ViewDimension = D3D12_DSV_DIMENSION::D3D12_DSV_DIMENSION_TEXTURE2D;

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += Dev->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * unsigned int(index);

	Dev->CreateDepthStencilView(rsc, &dsc, handle);
}

// マップ
long Descriptor::Map(ID3D12Resource* rsc, void** data)
{
	D3D12_RANGE range = { 0, 1 };
	auto hr = rsc->Map(0, &range, *(&data));
	if (FAILED(hr))
	{
		func::DebugLog("リソースマップ：失敗");
	}

	return hr;
}

// アンマップ
void Descriptor::UnMap(ID3D12Resource* rsc)
{
	if (rsc == nullptr)
	{
		return;
	}

	D3D12_RANGE range = { 0, 1 };
	rsc->Unmap(0, &range);
}
