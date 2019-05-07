#include "Texture.hlsl"

float4 main(Out o) : SV_TARGET
{
	float alpha = tex.Sample(smp, o.uv).a * color.a;
    if (alpha <= 0.0f)
    {
        discard;
    }

    return float4(tex.Sample(smp, o.uv).xyz, alpha);
}