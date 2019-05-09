#include "MyLib/MyLib.h"

int main()
{
	MyLib lib(640);
	Primitive p(PrimitiveType::box);
	p.pos[0] = Vec2f(0.0f, 0.0f);
	p.pos[1] = Vec2f(100.0f, 0.0f);
	p.pos[2] = Vec2f(0.0f, 100.0f);
	p.pos[3] = Vec2f(100.0f, 100.0f);

	Texture tex("Image/brides.png");
	tex.size = Vec2f(lib.GetWinSize().x, lib.GetWinSize().y);
	while (lib.CheckMsg())
	{
		lib.Clear();
		lib.Draw(p, Vec3f(1.0f, 0.0f, 0.0f));
		lib.Draw(tex);
		lib.Execution();
	}

	return 0;
}