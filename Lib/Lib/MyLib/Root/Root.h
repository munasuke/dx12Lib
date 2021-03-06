#pragma once
#include "../etc/Define.h"
#include <string>

class Root
{
public:
	// コンストラクタ
	Root();
	// デストラクタ
	~Root();

	// 頂点シェーダコンパイル
	void Vertex(const std::string& fileName, const std::string& func, const std::string& ver);

	// ピクセルシェーダコンパイル
	void Pixel(const std::string& fileName, const std::string& func, const std::string& ver);

	// .cso読み込み
	void Vertex(const std::string& fileName);
	void Pixel(const std::string& fileName);

	void Vertex(const int& id);
	void Pixel(const int& id);

	// ルート取得
	ID3D12RootSignature* Get() const;
	// 頂点シェーダ取得
	ID3DBlob* Vertex() const;
	// ピクセルシェーダ取得
	ID3DBlob* Pixel() const;

private:
	Root(const Root&) = delete;
	void operator=(const Root&) = delete;

	// シェーダコンパイル
	long Compile(const std::string& fileName, const std::string& func, const std::string& ver, ID3DBlob** blob);

	// .cso読み込み
	long Load(const std::string& fileName, ID3DBlob** blob);

	// リソース読み込み
	long Read(const int& id, ID3DBlob** blob);

	// ルート情報取得
	long RootInfo(ID3DBlob* blob);

	// ルートシグネチャ生成
	long CreateRoot();


	// ルート
	ID3D12RootSignature* root;

	// シグネチャ
	ID3DBlob* sig;

	// 頂点シェーダ
	ID3DBlob* vertex;

	// ピクセルシェーダ
	ID3DBlob* pixel;
};
