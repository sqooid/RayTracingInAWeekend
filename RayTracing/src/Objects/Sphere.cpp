#include "pch.h"
#include "Sphere.h"

HitRecord Sphere::hit(const Ray& ray, float tMin, float tMax) const
{
	glm::vec3 oc = ray.origin - m_Center;
	float a = glm::dot(ray.direction, ray.direction);
	float b = 2 * glm::dot(oc, ray.direction);
	float c = glm::dot(oc, oc) - m_Radius * m_Radius;
	float disc = b * b - 4 * a * c;
	if (disc < 0)
	{
		return HitRecord();
	}
	float t = (-b - std::sqrt(disc)) / (2 * a);
	if (t <= tMin)
	{
		t = (-b + std::sqrt(disc)) / (2 * a);
		if (t <= tMin)
		{
			return HitRecord();
		}
	}
	if (t <= tMax)
	{
		return HitRecord(ray, ray.at(t), glm::normalize(ray.at(t) - m_Center), t);
	}
	return HitRecord();
}
