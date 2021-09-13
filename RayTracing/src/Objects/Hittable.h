#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "Ray.h"

class Material;

struct HitRecord
{
	HitRecord() :
		collides(false), point(), normal(), t(), front(), material() {}

	HitRecord(const Ray& ray, const glm::vec3& normal, float t, std::shared_ptr<Material> material) :
		collides(true), point(ray.at(t)), normal(glm::normalize(normal)), t(t), material(material), front()
	{
		front = glm::dot(ray.direction, normal) < 0.0f;
		if (!front)
		{
			this->normal = -normal;
		}
	}

	bool collides;
	glm::vec3 point;
	glm::vec3 normal;
	float t;
	std::shared_ptr<Material> material;
	bool front;
};

struct Hittable
{
	virtual HitRecord hit(const Ray& ray, float tMin, float tMax) const = 0;
};

class HittableList
{
public:
	HittableList() = default;

	void add(std::shared_ptr<Hittable> hittable);
	HitRecord hit(const Ray& ray, float tMin, float tMax) const;
private:
	std::vector<std::shared_ptr<Hittable>> m_List;
};