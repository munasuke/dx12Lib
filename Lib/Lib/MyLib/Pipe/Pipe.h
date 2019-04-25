#pragma once
#include "../etc/Define.h"

class Pipe
{
public:
	// コンストラクタ
	Pipe(std::weak_ptr<Root>root, const D3D12_INPUT_ELEMENT_DESC& input, const size_t& num, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const bool& depth);
	// デストラクタ
	~Pipe();

	// パイプライン取得
	ID3D12PipelineState* Get(void) const;

private:
	Pipe(const Pipe&) = delete;
	void operator=(const Pipe&) = delete;

	// パイプライン生成
	long CreatePipe(const D3D12_INPUT_ELEMENT_DESC& input, const size_t& num, const D3D12_PRIMITIVE_TOPOLOGY_TYPE& type, const bool& depth);


	// ルート
	std::weak_ptr<Root>root;

	// パイプライン
	ID3D12PipelineState* pipe;
};
