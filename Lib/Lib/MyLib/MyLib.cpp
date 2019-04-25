#include "MyLib.h"
#include "Window/Window.h"
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

// �R���X�g���N�^
MyLib::MyLib(const Vec2& size, const Vec2& pos)
{
	Instance(pos, size, nullptr);
}

// �R���X�g���N�^
MyLib::MyLib(const MyLib& lib, const Vec2& size, const Vec2& pos)
{
	Instance(pos, size, lib.win->Get());
}

// �R���X�g���N�^
MyLib::MyLib(std::weak_ptr<MyLib>lib, const Vec2& size, const Vec2& pos)
{
	Instance(pos, size, lib.lock()->win->Get());
}

// �f�X�g���N�^
MyLib::~MyLib()
{
}

// �N���X�̃C���X�^���X
void MyLib::Instance(const Vec2& pos, const Vec2& size, void* parent)
{
#ifdef _DEBUG
	ID3D12Debug* debug = nullptr;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
	debug->EnableDebugLayer();
#endif

	win = std::make_shared<Window>(pos, size, parent);
}

// �^�C�g�����ύX
void MyLib::ChangeTitle(const std::string& title) const
{
	SetWindowTextA(HWND(win->Get()), title.c_str());
}

// �E�B���h�E���W�擾
Vec2 MyLib::GetWinPos(void) const
{
	RECT rect{};
	GetWindowRect(HWND(win->Get()), &rect);
	return Vec2(int(rect.left), int(rect.top));
}

// �E�B���h�E�T�C�Y�擾
Vec2 MyLib::GetWinSize(void) const
{
	RECT rect{};
	GetClientRect(HWND(win->Get()), &rect);
	return Vec2(int(rect.right), int(rect.bottom));
}

// ���b�Z�[�W�m�F
bool MyLib::CheckMsg(void) const
{
	static MSG msg{};

	if (msg.message == WM_QUIT)
	{
		return false;
	}

	//�Ăяo�����X���b�h�����L���Ă���E�B���h�E�ɑ��M���ꂽ���b�Z�[�W�ۗ̕�����Ă��镨���擾
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�
		TranslateMessage(&msg);
		//1�̃E�B�h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗏o����
		DispatchMessage(&msg);
	}

	return true;
}

// ��ʃN���A
void MyLib::Clear(void) const
{
}

// ���s
void MyLib::Execution(void) const
{
}
