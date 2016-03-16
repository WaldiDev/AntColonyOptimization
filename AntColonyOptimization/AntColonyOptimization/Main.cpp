#include "SfmlWindow.h"

int main()
{
	auto windowWidth = 1600u;
	auto windowHeight = 1000u;

	SfmlWindow window(windowWidth, windowHeight);
	window.Run();

	return 0;
}
