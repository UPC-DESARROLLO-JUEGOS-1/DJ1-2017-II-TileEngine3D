#include "Randomizer.h"
#include <functional>

Randomizer::Randomizer()
{
}

Randomizer::~Randomizer()
{
}

long Randomizer::GenerateRandom(int min, int max) {
	std::random_device dev;
	std::mt19937 engine(dev());
	std::uniform_int_distribution<int> distribution(min, max);
	return long(distribution(engine));
}