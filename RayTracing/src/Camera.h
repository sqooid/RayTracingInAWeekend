#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

class Camera
{
public:
	Camera() = default;
	Camera(glm::vec3 origin, glm::vec3 direction, float aspectRatio, float fov, float minDistance);

	Ray getRay(float u, float v);

private:
	glm::vec3 m_Origin;
	float m_MinDistance;
	glm::vec3 m_Width;
	glm::vec3 m_Height;
	float m_AspectRatio;
	glm::vec3 m_Corner;
};

