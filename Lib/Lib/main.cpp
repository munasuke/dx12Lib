#include"Device\Device.h"
#include <Windows.h>

#pragma comment(lib, "d3d12.lib")

int main()
{
	Device::Get().GetDev();

	return 0;
}