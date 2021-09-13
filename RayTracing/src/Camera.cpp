#include "pch.h"
#include "Camera.h"

Camera::Camera(glm::vec3 origin, glm::vec3 direction, float aspectRatio, float fov, float minDistance) :
	m_Origin(origin), m_MinDistance(minDistance), m_Width(), m_Height(), m_AspectRatio(aspectRatio), m_Corner()
{
	float width = 2 * minDistance * glm::tan(glm::radians(fov / 2));
	m_Width = width * glm::normalize(glm::cross(direction, glm::vec3(0.0, 1.0, 0.0)));
	float height = width / aspectRatio;
	m_Height = height * glm::normalize(glm::cross(direction, -m_Width));
	m_Corner = origin + minDistance * direction - 0.5f * m_Width - 0.5f * m_Height;
}

Ray Camera::getRay(float u, float v)
{
	return Ray(m_Origin, m_Corner + u * m_Width + v * m_Height - m_Origin);
}
