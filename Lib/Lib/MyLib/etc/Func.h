#pragma once
#include <string>

namespace func
{
	// �f�o�b�O�o��
	void DebugLog(const std::string& st);

	// �����R�[�h�ϊ�
	std::wstring ChangeCode(const std::string& code);
	std::string ChangeCode(const std::wstring& code);
}
