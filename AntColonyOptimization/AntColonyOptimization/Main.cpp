#include "SfmlWindow.h"

int main()
{
	auto windowWidth = 1280;
	auto windowHeight = 720u;

	SfmlWindow window(windowWidth, windowHeight);
	window.Run();

	return 0;
}
