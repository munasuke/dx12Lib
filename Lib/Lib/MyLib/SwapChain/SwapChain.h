#pragma once
#include "../etc/Define.h"

class SwapChain
{
public:
	SwapChain(std::weak_ptr<Window> win, std::weak_ptr<Queue> queue);
	~SwapChain();

	IDXGISwapChain4* Get()const;
private:
	// �t�@�N�g���[����
	long CreateFactory();

	// �X���b�v�`�F�C������
	long CreateSwapChain(std::weak_ptr<Window> win, std::weak_ptr<Queue> queue);

	IDXGIFactory4* factory;
	IDXGISwapChain4* swap;
};