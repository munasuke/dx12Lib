#pragma once
#include "../etc/Define.h"
#include "../etc/Func.h"
#include <unordered_map>

class TexLoader
{
public:
	~TexLoader();
	static TexLoader& Get();

	// 読み込み
	long Load(const std::string& filePath);

	// 削除
	void Delete(const std::string& filePath);

	// リソース取得
	ID3D12Resource* GetRsc(const std::string& filePath);

	// デコード取得
	unsigned char* GetDec(const std::string& filePath);

	// サブリソース取得
	std::shared_ptr<D3D12_SUBRESOURCE_DATA> GetSub(const std::string& filePath);
private:
	TexLoader();
	TexLoader(const TexLoader&) = delete;
	void operator=(const TexLoader&) = delete;

	// リソース
	std::unordered_map<std::string, ID3D12Resource*> rsc;

	// デコード
	std::unordered_map<std::string, std::unique_ptr<unsigned char[]>> dec;

	// サブリソース
	std::unordered_map<std::string, std::shared_ptr<D3D12_SUBRESOURCE_DATA>> sub;
};