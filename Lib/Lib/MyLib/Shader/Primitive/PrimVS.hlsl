#include "Primitive.hlsl"

[RootSignature(RS)]
Out main(Input input)
{
	Out o;
	o.svpos = input.pos;
	o.pos   = input.pos;

	return o;
}