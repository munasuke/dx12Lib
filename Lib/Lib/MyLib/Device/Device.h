#pragma once
#include "../etc/Define.h"

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

	long CreateDevice();

	ID3D12Device* dev;
};