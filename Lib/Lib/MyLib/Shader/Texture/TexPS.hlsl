#include "Texture.hlsl"

float4 main(Out o) : SV_TARGET
{
	if (tex.Sample(smp, o.uv).a <= 0.0f)
	{
		discard;
	}

	return tex.Sample(smp, o.uv);
}