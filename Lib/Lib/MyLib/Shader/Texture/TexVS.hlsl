#include "Texture.hlsl"

[RootSignature(RS)]
Out main(Input input)
{
    Out o;

	float2 pos = input.pos.xy / (float2(640, -640) / 2) + float2(-1, 1);
    o.svpos = float4(pos.xy, input.pos.zw);
    o.pos   = float4(pos.xy, input.pos.zw);
    o.uv    = input.uv;

	return o;
}