#include "pch.h"

#include "Utility.h"

#include <random>

static std::random_device rd;
static std::mt19937 e2(rd());
static std::uniform_real_distribution<> dist(0, 1);

float randFloat()
{
	return dist(e2);
}

float randFloat(float min, float max)
{
	return randFloat() * (max - min) + min;
}
