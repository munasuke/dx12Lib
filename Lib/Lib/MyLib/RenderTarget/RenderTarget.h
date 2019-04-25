#pragma once
#include "../etc/Define.h"
#include <vector>

class RenderTarget
{
public:
	RenderTarget(std::weak_ptr<SwapChain> swap);
	~RenderTarget();

	void Clear(std::weak_ptr<List> list);

	ID3D12Resource* GetRsc()const;
private:
	long CreateRenderTarget();

	std::weak_ptr<SwapChain> swap;

	std::vector<ID3D12Resource*> rsc;
	ID3D12DescriptorHeap* heap;
};