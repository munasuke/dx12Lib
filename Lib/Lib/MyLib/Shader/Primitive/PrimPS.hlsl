#include "Primitive.hlsl"

float4 main(Out o) : SV_TARGET
{
	if (color.a <= 0.0f)
	{
		discard;
	}

	return color;
}