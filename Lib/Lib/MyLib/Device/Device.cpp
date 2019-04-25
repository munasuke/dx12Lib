#include "Device.h"
#include "../etc/Func.h"
#include "../etc/Release.h"

// 機能レベル一覧
D3D_FEATURE_LEVEL level[] = {
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_1,
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_0,
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0
};

Device::Device() :
	dev(nullptr)
{
	CreateDevice();
}

Device::~Device()
{
	Release(dev);
}

Device& Device::Get()
{
	static Device instance;
	return instance;
}

long Device::CreateDevice()
{
	long hr = S_OK;
	for (D3D_FEATURE_LEVEL& i : level)
	{
		hr = D3D12CreateDevice(nullptr, i, IID_PPV_ARGS(&dev));
		if (hr == S_OK)
		{
			func::DebugLog("デバイス生成：成功");
			break;
		}
	}

	return hr;
}

ID3D12Device * Device::GetDev() const
{
	return dev;
}
