#pragma once
#include "../etc/Define.h"

struct IDXGIFactory;

class Device
{
public:
	~Device();

	static Device& Get();

	ID3D12Device* GetDev()const;
	IDXGIFactory4* GetFactory()const;
private:
	Device();
	Device(const Device&) = delete;
	void operator=(const Device&) = delete;

	long CreateFactory();
	long CreateDevice();

	IDXGIFactory4* factory;
	ID3D12Device* dev;
};