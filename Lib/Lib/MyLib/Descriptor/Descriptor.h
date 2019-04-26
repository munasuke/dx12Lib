#pragma once
#include "../etc/Define.h"

class Descriptor
{
public:
	~Descriptor();
	static Descriptor& Get();

	// ヒープ生成
	long CreateHeap(ID3D12DescriptorHeap** heap, const D3D12_DESCRIPTOR_HEAP_TYPE& type, const D3D12_DESCRIPTOR_HEAP_FLAGS& flag,
		const size_t& descriptorNum = 1);

	// リソース生成
	long CreateRsc(ID3D12Resource** rsc, const D3D12_HEAP_PROPERTIES& hprop, D3D12_RESOURCE_DESC& dsc,
		const D3D12_RESOURCE_STATES& state, const D3D12_CLEAR_VALUE* clear = nullptr);

	// RTV
	void RTV(ID3D12Resource& rsc, ID3D12DescriptorHeap& heap, const size_t& index = 0);

	// SRV生成
	void SRV(ID3D12Resource& rsc, ID3D12DescriptorHeap& heap, const size_t& index = 0);

	// CBV生成
	void CBV(ID3D12Resource& rsc, ID3D12DescriptorHeap& heap, const size_t& index = 0);

	// DSV生成
	void DSV(ID3D12Resource& rsc, ID3D12DescriptorHeap& heap, const size_t& index = 0);

	// マップ
	long Map(ID3D12Resource* rsc, void** data);

	// アンマップ
	void UnMap(ID3D12Resource* rsc);

private:
	Descriptor();
};
