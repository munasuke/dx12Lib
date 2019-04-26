#pragma once
#include "../etc/Define.h"
#include "../etc/Func.h"
#include <unordered_map>

class TexLoader
{
public:
	~TexLoader();
	static TexLoader& Get();

	// �ǂݍ���
	long Load(const std::string& filePath);

	// �폜
	void Delete(const std::string& filePath);

	// ���\�[�X�擾
	ID3D12Resource* GetRsc(const std::string& filePath);

	// �f�R�[�h�擾
	unsigned char* GetDec(const std::string& filePath);

	// �T�u���\�[�X�擾
	std::shared_ptr<D3D12_SUBRESOURCE_DATA> GetSub(const std::string& filePath);
private:
	TexLoader();
	TexLoader(const TexLoader&) = delete;
	void operator=(const TexLoader&) = delete;

	// ���\�[�X
	std::unordered_map<std::string, ID3D12Resource*> rsc;

	// �f�R�[�h
	std::unordered_map<std::string, std::unique_ptr<unsigned char[]>> dec;

	// �T�u���\�[�X
	std::unordered_map<std::string, std::shared_ptr<D3D12_SUBRESOURCE_DATA>> sub;
};