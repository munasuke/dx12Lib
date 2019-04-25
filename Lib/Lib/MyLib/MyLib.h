#pragma once
#include "etc/Define.h"
#include "etc/Vector2.h"
#include <string>

class MyLib
{
public:
	// �R���X�g���N�^
	MyLib(const Vec2& size, const Vec2& pos = 0x80000000);
	MyLib(const MyLib& lib, const Vec2& size, const Vec2& pos = 0x80000000);
	MyLib(std::weak_ptr<MyLib>lib, const Vec2& size, const Vec2& pos = 0x80000000);
	// �f�X�g���N�^
	~MyLib();

	// �^�C�g�����ύX
	void ChangeTitle(const std::string& title) const;

	// �E�B���h�E���W�擾
	Vec2 GetWinPos(void) const;

	// �E�B���h�E�T�C�Y�擾
	Vec2 GetWinSize(void) const;

	// ���b�Z�[�W�m�F
	bool CheckMsg(void) const;

	// ��ʃN���A
	void Clear(void) const;

	// ���s
	void Execution(void) const;

private:
	MyLib(const MyLib&) = delete;
	void operator=(const MyLib&) = delete;

	// �N���X�̃C���X�^���X
	void Instance(const Vec2& pos, const Vec2& size, void* parent);


	// �E�B���h�E
	std::shared_ptr<Window>win;
};
