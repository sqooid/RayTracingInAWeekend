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

glm::vec3 randInSphere()
{
	while (true)
	{
		glm::vec3 point(randFloat(-1, 1), randFloat(-1, 1), randFloat(-1, 1));
		if (glm::dot(point, point) < 1)
		{
			return point;
		}
	}
}

glm::vec3 randUnitVector()
{
	return glm::normalize(glm::vec3(randFloat(-1, 1), randFloat(-1, 1), randFloat(-1, 1)));
}

bool vecNearZero(const glm::vec3& vec)
{
	const float min = 1e-8;
	return vec.x < min&& vec.y < min&& vec.z < min;
}

glm::vec3 reflect(const glm::vec3& source, const glm::vec3& normal)
{
	return glm::vec3(source - 2.0f * glm::dot(source, normal) * normal);
}

glm::vec3 refract(const glm::vec3& source, const glm::vec3& normal, float e)
{
	auto cosT = glm::dot(-source, normal);
	auto perp = e * (source + cosT * normal);
	auto para = -std::sqrt(std::abs(1.0f - glm::dot(perp, perp))) * normal;
	return perp + para;
}

float reflectance(float cosT, float indexRefrac)
{
	auto r0 = (1.0f - indexRefrac) / (1.0f + indexRefrac);
	r0 *= r0;
	return r0 + (1.0f - r0) * std::pow(1.0f - cosT, 5);
}
