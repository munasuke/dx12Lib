#pragma once
#include "InputKey.h"

class Input
{
public:
	~Input();
	static Input& Get();

	// ’·‰Ÿ‚µ
	bool IsKey(const Key& key);

	// ƒgƒŠƒK[
	bool IsTrigger(const Key& key);
private:
	Input();
	Input(const Input&) = delete;
	void operator=(const Input&) = delete;

	bool now[0x100];
	bool old[0x100];
};