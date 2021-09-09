#pragma once

#include "Hittable.h"

class Sphere :
	public Hittable
{
public:
	Sphere(const glm::vec3& center, float radius) :
		m_Center(center), m_Radius(radius) {}

	HitRecord hit(const Ray& ray, float tMin, float tMax) const override;

private:
	glm::vec3 m_Center;
	float m_Radius;
};