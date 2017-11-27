#pragma once
#include <random>

class Randomizer
{
public:
	Randomizer();
	~Randomizer();
	long GenerateRandom(int min, int max);
};

