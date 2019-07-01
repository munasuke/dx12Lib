#include "TexLoader.h"
#include "../etc/Release.h"
#include "WICTextureLoader12.h"
#include <d3d12.h>

TexLoader::TexLoader()
{
}

TexLoader::~TexLoader()
{
	rsc.clear();
	dec.clear();
	sub.clear();
}

TexLoader& TexLoader::Get()
{
	static TexLoader instance;
	return instance;
}

// �ǂݍ���
long TexLoader::Load(const std::string& filePath)
{
	if (rsc.find(filePath) != rsc.end())
	{
		return S_OK;
	}

	sub[filePath] = std::make_shared<D3D12_SUBRESOURCE_DATA>();
	auto wstr = func::ChangeCode(filePath);
	auto hr = DirectX::LoadWICTextureFromFile(Dev, wstr.c_str(), &rsc[filePath], dec[filePath], *sub[filePath]);
	if (FAILED(hr))
	{
		func::DebugLog("�摜�ǂݍ��݁F���s");
	}

	return hr;
}

// �폜
void TexLoader::Delete(const std::string& filePath)
{
	if (rsc.find(filePath) != rsc.end())
	{
		rsc.erase(filePath);
		dec.erase(filePath);
		sub.erase(filePath);
	}
}

// ���\�[�X�擾
ID3D12Resource* TexLoader::GetRsc(const std::string& filePath) 
{
	if (rsc.find(filePath) == rsc.end())
	{
		return nullptr;
	}

	return rsc[filePath];
}

// �f�R�[�h�擾
unsigned char* TexLoader::GetDec(const std::string& filePath) 
{
	if (dec.find(filePath) == dec.end())
	{
		return nullptr;
	}

	return dec[filePath].get();
}

// �T�u���\�[�X�擾
std::shared_ptr<D3D12_SUBRESOURCE_DATA> TexLoader::GetSub(const std::string& filePath)
{
	if (sub.find(filePath) == sub.end())
	{
		return nullptr;
	}

	return sub[filePath];
}

Vec2f TexLoader::GetSize(const std::string& filePath)
{
	return Vec2f(float(rsc[filePath]->GetDesc().Width), 
		float(rsc[filePath]->GetDesc().Height));
}
