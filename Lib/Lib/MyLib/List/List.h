#pragma once
#include "../etc/Define.h"
#include "../etc/Vector2.h"

class List
{
public:
	// コンストラクタ
	List(const D3D12_COMMAND_LIST_TYPE& type);
	// デストラクタ
	~List();

	// リセット
	void Reset(ID3D12PipelineState* pipe = nullptr) const;

	// ビューポートセット
	void Viewport(const Vec2& size) const;

	// シザーセット
	void Scissor(const Vec2& size) const;

	// バリアセット
	void Barrier(const D3D12_RESOURCE_STATES& befor, const D3D12_RESOURCE_STATES& affter, ID3D12Resource* rsc) const;

	// ルートシグネチャセット
	void SetRoot(std::weak_ptr<Root>root) const;

	// パイプラインのセット
	void SetPipe(std::weak_ptr<Pipe>pipe) const;

	// ヒープセット
	void SetHeap(ID3D12DescriptorHeap** heap, const size_t& num) const;

	// ルートとヒープの関連付け
	void GraphicTable(const unsigned int& id, ID3D12DescriptorHeap* heap, const unsigned int& index) const;

	// 頂点バッファビューセット
	void VertexView(const D3D12_VERTEX_BUFFER_VIEW& view) const;

	// インデックスバッファビューセット
	void IndexView(const D3D12_INDEX_BUFFER_VIEW& view) const;

	// トポロジーセット
	void Topology(const D3D_PRIMITIVE_TOPOLOGY& type) const;

	// 頂点描画
	void DrawVertex(const size_t& num, const unsigned int& instance = 1) const;

	// バンドル実行
	void Bundle(List* list) const;

	// リスト閉じる
	void Close(void) const;

	// アロケータ取得
	ID3D12CommandAllocator* GetAllo(void) const;

	// リスト取得
	ID3D12GraphicsCommandList* GetList(void) const;

private:
	List(const List&) = delete;
	void operator=(const List&) = delete;

	// アロケータ生成
	long CreateAllo(const D3D12_COMMAND_LIST_TYPE& type);

	// リスト生成
	long CreateList(const D3D12_COMMAND_LIST_TYPE& type);


	// アロケータ
	ID3D12CommandAllocator* allo;

	// リスト
	ID3D12GraphicsCommandList* list;
};
