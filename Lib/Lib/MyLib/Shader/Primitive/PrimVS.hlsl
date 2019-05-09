#include "Primitive.hlsl"

[RootSignature(RS)]
Out main(Input input)
{
	input.pos.xy = input.pos.xy / (float2(window.x, -window.x) / 2) + float2(-1, 1);

	Out o;
	o.svpos = input.pos;
	o.pos   = input.pos;

	return o;
}