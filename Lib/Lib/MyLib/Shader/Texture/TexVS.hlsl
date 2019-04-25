#include "Texture.hlsl"

[RootSignature(RS)]
Out main(Input input)
{
    Out o;
    o.svpos = input.pos;
    o.pos   = input.pos;
    o.uv    = input.uv;

	return o;
}