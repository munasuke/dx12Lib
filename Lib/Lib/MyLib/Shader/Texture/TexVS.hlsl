#include "Texture.hlsl"

[RootSignature(RS)]
Out main(Input input)
{
	float2 size = float2(0.0f, 0.0f);
	tex.GetDimensions(size.x, size.y);

	input.pos    = mul(mat, input.pos);
	input.pos.xy = input.pos.xy / (float2(window.x, -window.x) / 2) + float2(-1, 1);
	float2 tmp = (fmod((input.uv + reverse), 2.0f) * uvSize + uvPos) / size;
	input.uv = tmp;
	//input.uv = int2(tmp.x, tmp.y);

	Out o;
	o.svpos = input.pos;
	o.pos   = input.pos;
    o.uv    = input.uv;

	return o;
}