#include "MyLib/MyLib.h"

int main()
{
	MyLib lib(640);
	while (lib.CheckMsg())
	{
		lib.Clear();
		lib.Execution();
	}

	return 0;
}