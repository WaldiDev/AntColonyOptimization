#pragma once
class RandomNumberGenerator
{
public:
	RandomNumberGenerator();
	~RandomNumberGenerator();

	int RandomRange(int min, int max) const;
};

