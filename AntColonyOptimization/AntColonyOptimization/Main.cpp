#include "SfmlWindow.h"
#include "RandomNumberGenerator.h"

int main()
{
	auto windowWidth = 1280;
	auto windowHeight = 720u;

	RandomNumberGenerator::InitRandom();

	SfmlWindow window(windowWidth, windowHeight);
	window.Run();

	return 0;
}
