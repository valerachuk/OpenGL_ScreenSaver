#include "Utils.h"


Utils::Utils()
{
	std::srand(std::time(nullptr));
}

int Utils::getRandomInt(int a, int b)
{
	return std::rand() % (b - a) + a;
}

float Utils::getRandomFloat(float a, float b)
{
	return getRandomInt(a * 1000, b * 1000) / 1000.0f;
}

Utils& Utils::getInstance()
{
	static Utils inst;
	return inst;
}
