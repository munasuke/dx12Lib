#pragma once
#include "../etc/Define.h"

class SwapChain
{
public:
	SwapChain(std::weak_ptr<Window> win, std::weak_ptr<Queue> queue);
	~SwapChain();

	IDXGISwapChain4* Get()const;
private:
	// ファクトリー生成
	long CreateFactory();

	// スワップチェイン生成
	long CreateSwapChain(std::weak_ptr<Window> win, std::weak_ptr<Queue> queue);

	IDXGIFactory4* factory;
	IDXGISwapChain4* swap;
};