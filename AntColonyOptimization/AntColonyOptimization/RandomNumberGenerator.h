#pragma once
class RandomNumberGenerator
{
public:
	RandomNumberGenerator();
	~RandomNumberGenerator();
	static void InitRandom();
	static float GetRandom();
};

