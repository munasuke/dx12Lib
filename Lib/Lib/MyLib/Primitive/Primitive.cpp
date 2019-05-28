#include "Primitive.h"
#include "../etc/Release.h"

// コンストラクタ
Primitive::Primitive()
{
	Init();
}

// コンストラクタ
Primitive::Primitive(const PrimitiveType& type)
{
	Init();
	Reset(type, unsigned int(type));
}

// コンストラクタ
Primitive::Primitive(const PrimitiveType& type, const unsigned int& num)
{
	Init();
	Reset(type, num);
}

// コピーコンストラクタ
Primitive::Primitive(const Primitive& prim)
{
	(*this) = prim;
}

// デストラクタ
Primitive::~Primitive()
{
	Desc.UnMap(rsc);
	Desc.UnMap(cRsc);
	Release(rsc);
	Release(cRsc);
	Release(heap);
}

// 初期化
void Primitive::Init(void)
{
	rsc  = nullptr;
	cRsc = nullptr;
	data = nullptr;
	cData = nullptr;
	heap = nullptr;
	type = -1;
	color = DirectX::XMFLOAT4(1, 1, 1, 1);

	Desc.CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);
	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
	prop.Type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Flags = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE;
	desc.Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.Height = 1;
	desc.Layout = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels = 1;
	desc.SampleDesc = { 1, 0 };
	desc.Width = (sizeof(Data) + 0xff) & ~0xff;

	Desc.CreateRsc(&cRsc, prop, desc, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);

	Desc.CBV(cRsc, heap);

	Desc.Map(cRsc, (void**)(&cData));
}

// リセット
void Primitive::Reset(const PrimitiveType& type, const unsigned int& num)
{
	switch (type)
	{
	case PrimitiveType::point:
		this->type = D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
		break;
	case PrimitiveType::line:
		this->type = D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINELIST;
		break;
	case PrimitiveType::triangle:
		this->type = D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;
	case PrimitiveType::box:
		this->type = D3D12_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		break;
	default:
		break;
	}

	pos.assign(num, 0.0f);

	D3D12_HEAP_PROPERTIES prop{};
	prop.Type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = sizeof(pos[0]) * num;

	Desc.CreateRsc(&rsc, prop, desc, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);

	Desc.Map(rsc, &data);
}

// データ更新
void Primitive::UpData(void) const
{
	memcpy(data, pos.data(), sizeof(pos[0]) * pos.size());
}

// 代入演算子オーバーロード
void Primitive::operator=(const Primitive& prim)
{
	pos  = prim.pos;
	
	PrimitiveType type = PrimitiveType::point;
	switch (prim.type)
	{
	case 1:
		type = PrimitiveType::point;
		break;
	case 2:
		type = PrimitiveType::line;
		break;
	case 4:
		type = PrimitiveType::triangle;
		break;
	case 5:
		type = PrimitiveType::box;
		break;
	default:
		break;
	}

	Reset(type, unsigned int(pos.size()));
}
