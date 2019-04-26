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
	Release(rsc);
}

// 初期化
void Primitive::Init(void)
{
	rsc  = nullptr;
	data = nullptr;
	type = -1;
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
