#pragma once
#include <cstdlib>
#include <iostream>
#include <ctime>

class Utils
{
private:
	Utils();
public:
	Utils(const Utils&) = delete;

	Utils& operator=(const Utils&) = delete;
	int getRandomInt(int a, int b);
	float getRandomFloat(float a, float b);

	static Utils& getInstance();
};