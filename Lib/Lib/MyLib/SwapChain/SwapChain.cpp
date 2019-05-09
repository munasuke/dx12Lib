#include "SwapChain.h"
#include "../Window/Window.h"
#include "../Queue/Queue.h"
#include "../etc/Release.h"
#include "../etc/Func.h"
#include <dxgi1_6.h>

#define BUFFER_COUNT 2;

SwapChain::SwapChain(std::weak_ptr<Window> win, std::weak_ptr<Queue> queue) :
	factory(nullptr), swap(nullptr)
{
	CreateFactory();
	CreateSwapChain(win, queue);
}

SwapChain::~SwapChain()
{
	Release(swap);
	Release(factory);
}

// ファクトリー生成
long SwapChain::CreateFactory()
{
	auto hr = CreateDXGIFactory(IID_PPV_ARGS(&factory));
	if (FAILED(hr))
	{
		func::DebugLog("ファクトリー生成：失敗");
	}

	return hr;
}

// スワップチェイン生成
long SwapChain::CreateSwapChain(std::weak_ptr<Window> win, std::weak_ptr<Queue> queue)
{
	RECT rec{};
	GetClientRect(HWND(win.lock()->Get()), &rec);

	DXGI_SWAP_CHAIN_DESC1 dsc{};
	dsc.BufferCount = BUFFER_COUNT;
	dsc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	dsc.Format      = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	dsc.Height      = rec.bottom;
	dsc.SampleDesc  = { 1, 0 };
	dsc.Stereo      = false;
	dsc.SwapEffect  = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	dsc.Width       = rec.right;

	auto hr = factory->CreateSwapChainForHwnd(queue.lock()->Get(), HWND(win.lock()->Get()), 
		&dsc, nullptr, nullptr, (IDXGISwapChain1**)(&swap));
	if (FAILED(hr))
	{
		func::DebugLog("スワップチェイン生成：失敗");
	}

	return hr;
}

void SwapChain::Present()
{
	swap->Present(1, 0);
}

IDXGISwapChain4* SwapChain::Get() const
{
	return swap;
}
