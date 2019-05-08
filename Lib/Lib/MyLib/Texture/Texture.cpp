#include "Texture.h"
#include "TexLoader.h"
#include "../Descriptor/Descriptor.h"
#include "../List/List.h"
#include "../Root/Root.h"
#include "../Pipe/Pipe.h"
#include "../etc/Release.h"
#include <d3d12.h>

#define RSC_MAX 3
#define VERT_MAX 4

// コンストラクタ
Texture::Texture(const std::string& filePath) :
	heap(nullptr), con(nullptr), data(nullptr)
{
	rsc.assign(RSC_MAX, nullptr);
	vert.assign(VERT_MAX, Vertex());

	Load(filePath);
}

// デストラクタ
Texture::~Texture()
{
	for (auto& r : rsc)
	{
		Release(r);
	}
	Release(heap);
}

// 読み込み
int Texture::Load(const std::string& filePath)
{
	// ヒープ生成
	Descriptor::Get().CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
		D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, RSC_MAX - 1);

	unsigned int index = 0;

	if (FAILED(TexLoader::Get().Load(filePath)))
	{
		return -1;
	}

	size = TexLoader::Get().GetSize(filePath);
	uvSize = size;
	rsc[index] = TexLoader::Get().GetRsc(filePath);
	Descriptor::Get().SRV(*rsc[index], *heap, index);
	WriteSubResource(filePath, index);

	++index;
	CreateCB(index);
	Descriptor::Get().CBV(*rsc[index], *heap, index);
	Desc.Map(rsc[index], (void**)&con);

	++index;
	if (FAILED(CreateVB(index)))
	{
		func::DebugLog("頂点リソース生成：失敗");
		return -1;
	}

	rsc[index]->Map(0, nullptr, &data);
	memcpy(data, vert.data(), sizeof(vert[0]) * vert.size());
	rsc[index]->Unmap(0, nullptr);

	return 0;
}

// 描画準備
unsigned int Texture::SetDraw(std::weak_ptr<List> list, std::weak_ptr<Root> root, std::weak_ptr<Pipe> pipe)
{
	list.lock()->SetRoot(root);
	list.lock()->SetPipe(pipe);

	con->reverse = reverse;
	con->uvPos   = uvPos;
	con->uvSize  = uvSize;

	D3D12_VERTEX_BUFFER_VIEW vbv{};
	vbv.BufferLocation = (*rsc.rbegin())->GetGPUVirtualAddress();
	vbv.SizeInBytes    = unsigned int(sizeof(vert[0]) * vert.size());
	vbv.StrideInBytes  = sizeof(vert[0]);

	list.lock()->GetList()->IASetVertexBuffers(0, 1, &vbv);

	list.lock()->SetHeap(&heap, 1);

	unsigned int index = 0;
	for (unsigned int i = 0; i < RSC_MAX - 1; ++i)
	{
		list.lock()->GraphicTable(i, heap, i);
		index = i;
	}

	return ++index;
}

// 描画
void Texture::Draw(std::weak_ptr<List> list)
{
	list.lock()->GetList()->IASetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	list.lock()->GetList()->DrawInstanced(4, 1, 0, 0);
}

// 定数リソース生成
long Texture::CreateCB(const unsigned int index)
{
	D3D12_HEAP_PROPERTIES hProp{};
	hProp.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	hProp.CreationNodeMask     = 1;
	hProp.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
	hProp.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;
	hProp.VisibleNodeMask      = 1;

	D3D12_RESOURCE_DESC dsc{};
	dsc.DepthOrArraySize = 1;
	dsc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	dsc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE;
	dsc.Format           = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	dsc.Height           = 1;
	dsc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	dsc.MipLevels        = 1;
	dsc.SampleDesc       = { 1, 0 };
	dsc.Width            = (sizeof(Constant) + 0xff) &~ 0xff;

	return Descriptor::Get().CreateRsc(&rsc[index], hProp, dsc, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);
}

// 頂点リソース生成
long Texture::CreateVB(const unsigned int index)
{
	D3D12_HEAP_PROPERTIES hProp{};
	hProp.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	hProp.CreationNodeMask     = 1;
	hProp.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
	hProp.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;
	hProp.VisibleNodeMask      = 1;

	D3D12_RESOURCE_DESC dsc{};
	dsc.DepthOrArraySize = 1;
	dsc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	dsc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE;
	dsc.Format           = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	dsc.Height           = 1;
	dsc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	dsc.MipLevels        = 1;
	dsc.SampleDesc       = { 1, 0 };
	dsc.Width            = sizeof(vert[0]) * vert.size();

	return Descriptor::Get().CreateRsc(&rsc[index], hProp, dsc, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);
}

// サブリソース書き込み
long Texture::WriteSubResource(const std::string& path, const size_t& index)
{
	auto sub = TexLoader::Get().GetSub(path);
	auto decode = TexLoader::Get().GetDec(path);

	D3D12_BOX box{};
	box.back   = 1;
	box.bottom = unsigned int(rsc[index]->GetDesc().Height);
	box.right  = unsigned int(rsc[index]->GetDesc().Width);

	auto hr = rsc[index]->WriteToSubresource(0, &box, decode, unsigned int(sub->RowPitch), unsigned int(sub->SlicePitch));
	if (FAILED(hr))
	{
		func::DebugLog("サブリソース書き込み：失敗");
	}

	return hr;
}

// 画像サイズ
Vec2 Texture::GetTexSize() const
{
	return Vec2();
}
