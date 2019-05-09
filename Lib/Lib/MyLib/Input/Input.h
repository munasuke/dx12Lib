#pragma once
#include "InputKey.h"

class Input
{
public:
	~Input();
	static Input& Get();

	// ������
	bool IsKey(const Key& key);

	// �g���K�[
	bool IsTrigger(const Key& key);
private:
	Input();
	Input(const Input&) = delete;
	void operator=(const Input&) = delete;

	bool now[0x100];
	bool old[0x100];
};