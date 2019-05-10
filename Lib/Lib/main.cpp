#include "MyLib/MyLib.h"
#include "MyLib/FPS/FPSCounter.h"

int main()
{
	MyLib lib(640);
	//Primitive p(PrimitiveType::box);
	//p.pos[0] = Vec2f(0.0f, 0.0f);
	//p.pos[1] = Vec2f(100.0f, 0.0f);
	//p.pos[2] = Vec2f(0.0f, 100.0f);
	//p.pos[3] = Vec2f(100.0f, 100.0f);
	//Vec3f color = Vec3f(1.0f, 0.0f, 0.0f);

	Texture tex("Image/brides.png");

	//CFPSCounter fps(10);

	while (lib.CheckMsg() && !Input::Get().IsKey(Key::Escape))
	{
		lib.Clear();
		//lib.Draw(p, color);
		lib.Draw(tex);
		lib.Execution();

		//printf("%f\n", fps.GetFPS());

		if (Input::Get().IsKey(Key::Num4))
		{
			tex.pos.x-=2.0f;
		}
		if (Input::Get().IsKey(Key::Num6))
		{
			tex.pos.x+=2.0f;
		}

		//tex.pos.y++;
	}

	return 0;
}