#pragma once

#include "Hittable.h"
#include "Materials.h"

class Sphere :
	public Hittable
{
public:
	Sphere(const glm::vec3& center, float radius, std::shared_ptr<Material> material) :
		m_Center(center), m_Radius(radius), m_Material(material) {}

	HitRecord hit(const Ray& ray, float tMin, float tMax) const override;

private:
	glm::vec3 m_Center;
	float m_Radius;
	std::shared_ptr<Material> m_Material;
};