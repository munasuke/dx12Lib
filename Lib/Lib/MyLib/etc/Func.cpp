#include "Func.h"
#include <Windows.h>

// デバッグ出力
void func::DebugLog(const std::string& st)
{
#ifdef _DEBUG
	std::string tmp = "\n" + st + "\n";
	OutputDebugStringA(tmp.c_str());
#endif
}

// 文字コード変換
std::wstring func::ChangeCode(const std::string& code)
{
	//サイズの取得
	auto byteSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, code.c_str(), -1, nullptr, 0);

	std::wstring wstr;
	wstr.resize(byteSize);

	//変換
	byteSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, code.c_str(), -1, &wstr[0], byteSize);

	return wstr;
}

// 文字コード変換
std::string func::ChangeCode(const std::wstring& code)
{
	//サイズの取得
	auto byteSize = WideCharToMultiByte(CP_ACP, 0, code.c_str(), -1, nullptr, 0, nullptr, nullptr);

	std::string str;
	str.resize(byteSize);

	//変換
	byteSize = WideCharToMultiByte(CP_ACP, 0, code.c_str(), static_cast<int>(code.size()), &str[0], byteSize, nullptr, nullptr);

	return str;
}
