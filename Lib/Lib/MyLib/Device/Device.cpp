#include "Device.h"
#include "../etc/Func.h"
#include "../etc/Release.h"
#include <vector>
#include <dxgi1_6.h>

// 機能レベル一覧
D3D_FEATURE_LEVEL level[] = {
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_1,
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_0,
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0
};

Device::Device() :
	factory(nullptr), dev(nullptr)
{
	CreateFactory();
	CreateDevice();
}

Device::~Device()
{
	Release(dev);
	Release(factory);
}

Device& Device::Get()
{
	static Device instance;
	return instance;
}

long Device::CreateFactory()
{
	auto hr = CreateDXGIFactory(IID_PPV_ARGS(&factory));
	if (FAILED(hr))
	{
		func::DebugLog("ファクトリー生成：失敗");
	}

	return hr;
}

long Device::CreateDevice()
{
	std::vector<IDXGIAdapter*> adapters;
	IDXGIAdapter* adapter = nullptr;
	for (unsigned int i = 0; factory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		adapters.push_back(adapter);
	}
	for (auto& ad : adapters)
	{
		DXGI_ADAPTER_DESC dsc{};
		ad->GetDesc(&dsc);
		std::wstring wstr = dsc.Description;
		if (wstr.find(L"NVIDIA") != std::wstring::npos)
		{
			adapter = ad;
			break;
		}
		if (wstr.find(L"AMD") != std::wstring::npos)
		{
			adapter = adapters[0];
			break;
		}
	}

	long hr = S_OK;
	for (D3D_FEATURE_LEVEL& i : level)
	{
		hr = D3D12CreateDevice(adapter, i, IID_PPV_ARGS(&dev));
		if (hr == S_OK)
		{
			func::DebugLog("デバイス生成：成功");
			Release(adapter);
			break;
		}
	}

	return hr;
}

ID3D12Device * Device::GetDev() const
{
	return dev;
}
