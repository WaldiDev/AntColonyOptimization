#include "RandomNumberGenerator.h"
#include <cstdlib>
#include <time.h>

RandomNumberGenerator::RandomNumberGenerator()
{
	
}


RandomNumberGenerator::~RandomNumberGenerator()
{
}

void RandomNumberGenerator::InitRandom()
{
	srand(static_cast<unsigned int>(time(nullptr)));
}

float RandomNumberGenerator::GetRandom()
{
	auto rndNumber = rand()/float(RAND_MAX);
	return rndNumber;
}
