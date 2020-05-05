#pragma once
#include <cstdlib>
#include <iostream>
#include <ctime>

class Random
{
private:
	Random();
public:
	Random(const Random&) = delete;

	Random& operator=(const Random&) = delete;
	int getRandomInt(int a, int b);
	float getRandomFloat(float a, float b);

	static Random& getInstance();
};