#pragma once
#include "../Device/Device.h"
#include "../Descriptor/Descriptor.h"
#include <d3d12.h>

#define Dev Device::Get().GetDev()
#define Factory Device::Get().GetFactory()
#define Desc Descriptor::Get()

#define Release(X) { if((X) != nullptr) (X)->Release(); (X) = nullptr; }
