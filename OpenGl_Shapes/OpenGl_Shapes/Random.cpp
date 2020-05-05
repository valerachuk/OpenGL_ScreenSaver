#include "Random.h"


Random::Random()
{
	std::srand(std::time(nullptr));
}

int Random::getRandomInt(int a, int b)
{
	return std::rand() % (b - a) + a;
}

float Random::getRandomFloat(float a, float b)
{
	return getRandomInt(a * 1000, b * 1000) / 1000.0f;
}

Random& Random::getInstance()
{
	static Random inst;
	return inst;
}
