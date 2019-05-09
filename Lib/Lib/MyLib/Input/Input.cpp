#include "Input.h"
#include <Windows.h>

Input::Input()
{
	memset(&now[0], 0, sizeof(now));
	memset(&old[0], 0, sizeof(old));
}

Input::~Input()
{
}

Input& Input::Get()
{
	static Input instance;
	return instance;
}

bool Input::IsKey(const Key& key)
{
	old[int(key)] = now[int(key)];
	now[int(key)] = (GetKeyState(int(key)) & 0x80);
	
	return now[int(key)];
}

bool Input::IsTrigger(const Key& key)
{
	if (IsKey(key) && (now[int(key)] != old[int(key)]))
	{
		return true;
	}

	return false;
}
