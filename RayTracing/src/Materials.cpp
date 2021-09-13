#include "pch.h"

#include "Materials.h"
#include "Utility.h"

std::tuple<Ray, glm::vec3> Lambertian::scatter(const Ray& ray, const HitRecord& rec) const
{
	auto direction = rec.normal + randUnitVector();
	if (vecNearZero(direction))
	{
		direction = rec.normal;
	}
	return { Ray(rec.point,direction), m_Albedo };
}

std::tuple<Ray, glm::vec3> Metal::scatter(const Ray& ray, const HitRecord& rec) const
{
	auto direction = reflect(ray.direction, rec.normal);
	return { Ray(rec.point,direction + m_Fuzz * randUnitVector()), m_Albedo };
}

std::tuple<Ray, glm::vec3> Dielectric::scatter(const Ray& ray, const HitRecord& rec) const
{
	float refracRatio = rec.front ? 1.0f / m_IndexRefrac : m_IndexRefrac;
	float cosT = glm::dot(-ray.direction, rec.normal);
	float sinT = std::sqrt(1.0f - cosT * cosT);
	glm::vec3 direction;
	if (refracRatio * sinT > 1.0f || reflectance(cosT, refracRatio) > randFloat())	// Reflection
	{
		direction = reflect(ray.direction, rec.normal);
	}
	else
	{
		direction = refract(ray.direction, rec.normal, refracRatio);
	}
	return { Ray(rec.point, direction), glm::vec3(1.0) };
}
