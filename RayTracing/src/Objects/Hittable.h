#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "Ray.h"

struct HitRecord
{
	HitRecord() :
		collides(false), point(), normal(), t(), front()
	{
	}
	HitRecord(const Ray& ray, glm::vec3 point, glm::vec3 normal, float t) :
		collides(true), point(point), normal(normal), t(t), front()
	{
		front = glm::dot(ray.direction, normal) < 0;
	}
	bool collides;
	glm::vec3 point;
	glm::vec3 normal;
	float t;
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