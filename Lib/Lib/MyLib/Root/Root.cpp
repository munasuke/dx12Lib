#include <d3dcompiler.h>
#include "Root.h"
#include "../etc/Func.h"
#include "../etc/Release.h"

// コンストラクタ
Root::Root() : 
	root(nullptr), sig(nullptr), vertex(nullptr), pixel(nullptr)
{
}

// デストラクタ
Root::~Root()
{
	Release(pixel);
	Release(vertex);
	Release(sig);
	Release(root);
}

// シェーダコンパイル
long Root::Compile(const std::string& fileName, const std::string& func, const std::string& ver, ID3DBlob** blob)
{
	auto pass = func::ChangeCode(fileName);
	auto hr = D3DCompileFromFile(pass.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, func.c_str(), ver.c_str(),
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, *(&blob), nullptr);
	if (FAILED(hr))
	{
		func::DebugLog("シェーダコンパイル：失敗");
	}

	return hr;
}

// .cso読み込み
long Root::Load(const std::string& fileName, ID3DBlob** blob)
{
	auto pass = func::ChangeCode(fileName);
	auto hr = D3DReadFileToBlob(pass.c_str(), blob);
	if (FAILED(hr))
	{
		func::DebugLog(".cso読み込み：失敗");
	}

	return hr;
}

// リソース読み込み
long Root::Read(const int& id, ID3DBlob** blob)
{
	// リソース情報取得
	HRSRC rsc = FindResource(nullptr, MAKEINTRESOURCE(id), L"Shader");
	if (rsc == nullptr)
	{
		func::DebugLog("リソース情報取得：失敗");
		return S_FALSE;
	}

	// リソース読み込み
	HANDLE handle = LoadResource(nullptr, rsc);
	if (handle == nullptr)
	{
		func::DebugLog("リソース読み込み：失敗");
		return S_FALSE;
	}
	
	// データ取得
	void* data = LockResource(handle);

	// サイズ取得
	size_t size = SizeofResource(nullptr, rsc);

	auto hr = D3DSetBlobPart(data, size, D3D_BLOB_PART::D3D_BLOB_PRIVATE_DATA, 0, data, size, blob);
	if (FAILED(hr))
	{
		return S_FALSE;
	}

	return hr;
}

// ルート情報取得
long Root::RootInfo(ID3DBlob* blob)
{
	auto hr = D3DGetBlobPart(blob->GetBufferPointer(), blob->GetBufferSize(), D3D_BLOB_PART::D3D_BLOB_ROOT_SIGNATURE, 0, &sig);
	if (FAILED(hr))
	{
		func::DebugLog("ルートシグネチャ情報取得：失敗");
	}

	return hr;
}

// ルートシグネチャ生成
long Root::CreateRoot(void)
{
	auto hr = Dev->CreateRootSignature(0, sig->GetBufferPointer(), sig->GetBufferSize(), IID_PPV_ARGS(&root));
	if (FAILED(hr))
	{
		func::DebugLog("ルートシグネチャ生成：失敗");
	}

	return hr;
}

// 頂点シェーダコンパイル
void Root::Vertex(const std::string& fileName, const std::string& func, const std::string& ver)
{
	Compile(fileName, func, ver, &vertex);
	RootInfo(vertex);
	CreateRoot();
}

// ピクセルシェーダコンパイル
void Root::Pixel(const std::string& fileName, const std::string& func, const std::string& ver)
{
	Compile(fileName, func, ver, &pixel);
}

// .cso読み込み
void Root::Vertex(const std::string& fileName)
{
	Load(fileName, &vertex);
	RootInfo(vertex);
	CreateRoot();
}

// .cso読み込み
void Root::Pixel(const std::string& fileName)
{
	Load(fileName, &pixel);
}

void Root::Vertex(const int& id)
{
	Read(id, &vertex);
	RootInfo(vertex);
	CreateRoot();
}

void Root::Pixel(const int& id)
{
	Read(id, &pixel);
}

// ルート取得
ID3D12RootSignature* Root::Get(void) const
{
	return root;
}

// 頂点シェーダ取得
ID3DBlob* Root::Vertex(void) const
{
	return vertex;
}

// ピクセルシェーダ取得
ID3DBlob* Root::Pixel(void) const
{
	return pixel;
}
