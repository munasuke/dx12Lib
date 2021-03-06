#pragma once
#include <memory>

//�񋓌^
enum D3D12_COMMAND_LIST_TYPE : int;
enum D3D12_DESCRIPTOR_HEAP_TYPE : int;
enum D3D12_DESCRIPTOR_HEAP_FLAGS : int;
enum D3D12_RESOURCE_STATES : int;
enum D3D_PRIMITIVE_TOPOLOGY : int;
enum D3D12_PRIMITIVE_TOPOLOGY_TYPE : int;

//�\����
struct ID3D12Device;
struct ID3D12CommandAllocator;
struct ID3D12GraphicsCommandList;
struct ID3D12CommandList;
struct ID3D12CommandQueue;
struct ID3D12Resource;
struct ID3D12DescriptorHeap;
struct D3D12_HEAP_PROPERTIES;
struct D3D12_RESOURCE_DESC;
struct D3D12_CLEAR_VALUE;
struct ID3D12RootSignature;
struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;
struct ID3D12PipelineState;
struct D3D12_VERTEX_BUFFER_VIEW;
struct D3D12_INDEX_BUFFER_VIEW;
struct D3D12_INPUT_ELEMENT_DESC;
struct ID3D12Fence;
struct IDXGIFactory4;
struct IDXGISwapChain4;
struct D3D12_SUBRESOURCE_DATA;

// �N���X
class Window;
class List;
class Queue;
class Fence;
class Root;
class Pipe;
class RenderTarget;
class SwapChain;
