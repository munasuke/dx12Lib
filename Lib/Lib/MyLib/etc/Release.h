#pragma once
#include "../Device/Device.h"
#include <d3d12.h>

#define Dev Device::Get().GetDev()

#define Release(X) { if((X) != nullptr) (X)->Release(); (X) = nullptr; }
