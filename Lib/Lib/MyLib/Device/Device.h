#pragma once
#include "../etc/Define.h"

struct IDXGIFactory;

class Device
{
public:
	~Device();

	static Device& Get();

	ID3D12Device* GetDev()const;
private:
	Device();
	Device(const Device&) = delete;
	void operator=(const Device&) = delete;

	long CreateFactory();
	long CreateDevice();

	IDXGIFactory* factory;
	ID3D12Device* dev;
};