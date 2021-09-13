#include "pch.h"
#include "Plane.h"

Plane::Plane(const glm::vec3& normal, float constant, std::shared_ptr<Material> material) :
	m_Normal(glm::normalize(normal)), m_Constant(constant), m_Material(material)
{
}

HitRecord Plane::hit(const Ray& ray, float tMin, float tMax) const
{
	float t = (m_Constant - glm::dot(m_Normal, ray.origin)) / glm::dot(m_Normal, ray.direction);
	if (t > tMin && t < tMax)
	{
		return HitRecord(ray, m_Normal, t, m_Material);
	}
	return HitRecord();
}
