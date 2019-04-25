#include "Device.h"
#include <d3d12.h>

Device::Device() :
	dev(nullptr)
{
	CreateDevice();
}

Device::~Device()
{
}

Device& Device::Get()
{
	static Device instance;
	return instance;
}

long Device::CreateDevice()
{
	auto hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&dev));
	if (FAILED(hr))
	{
		OutputDebugStringA("\n�f�o�C�X�����F���s\n");
	}

	return hr;
}

ID3D12Device * Device::GetDev() const
{
	return dev;
}
