#pragma once
#include <tuple>
#include <algorithm>
#include <glm/glm.hpp>

#include "Ray.h"
#include "Objects/Hittable.h"

class Material
{
public:
	virtual std::tuple<Ray, glm::vec3> scatter(const Ray& ray, const HitRecord& rec) const = 0;
};

//////////////////////////////////////////////////////////////////////////
// Lambertian (Diffuse)
class Lambertian :
	public Material
{

public:
	Lambertian() = default;
	Lambertian(const glm::vec3& albedo) :
		m_Albedo(albedo) {}

	std::tuple<Ray, glm::vec3> scatter(const Ray& ray, const HitRecord& rec) const override;
private:
	glm::vec3 m_Albedo;
};

//////////////////////////////////////////////////////////////////////////
// Metal (reflective)
class Metal :
	public Material
{

public:
	Metal() = default;
	Metal(const glm::vec3& albedo, float fuzz = 0) :
		m_Albedo(albedo), m_Fuzz(std::clamp(fuzz, 0.0f, 1.0f)) {}

	std::tuple<Ray, glm::vec3> scatter(const Ray& ray, const HitRecord& rec) const override;
private:
	glm::vec3 m_Albedo;
	float m_Fuzz;
};

//////////////////////////////////////////////////////////////////////////
// Dielectric (Transparent)
class Dielectric :
	public Material
{

public:
	Dielectric() = default;
	Dielectric(float indexRefrac) :
		m_IndexRefrac(indexRefrac) {}

	std::tuple<Ray, glm::vec3> scatter(const Ray& ray, const HitRecord& rec) const override;
private:
	float m_IndexRefrac;
};