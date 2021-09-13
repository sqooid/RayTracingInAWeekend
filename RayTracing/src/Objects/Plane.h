#pragma once

#include <glm/glm.hpp>

#include "Hittable.h"
#include "Materials.h"

class Plane :
	public Hittable
{
public:
	Plane() = default;
	Plane(const glm::vec3& normal, float constant, std::shared_ptr<Material> material);
	HitRecord hit(const Ray& ray, float tMin, float tMax) const override;
private:
	glm::vec3 m_Normal;
	float m_Constant;
	std::shared_ptr<Material> m_Material;
};

