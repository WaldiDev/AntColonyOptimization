#include "RandomNumberGenerator.h"
#include <cstdlib>
#include <time.h>
#include <SFML/Graphics.hpp>

RandomNumberGenerator::RandomNumberGenerator()
{
	srand(time(nullptr));
}


RandomNumberGenerator::~RandomNumberGenerator()
{
}

int RandomNumberGenerator::RandomRange(int min, int max) const
{
	// Todo: Check if max is smaller than min.
	auto rndNumber = min + (rand() % static_cast<int>(max - min + 1));
	return rndNumber;
}
