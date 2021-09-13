#pragma once

#include <glm/glm.hpp>

float randFloat();
float randFloat(float min, float max);
glm::vec3 randInSphere();
glm::vec3 randUnitVector();
bool vecNearZero(const glm::vec3& vec);
glm::vec3 reflect(const glm::vec3& source, const glm::vec3& normal);
glm::vec3 refract(const glm::vec3& source, const glm::vec3& normal, float e);
float reflectance(float cosT, float indexRefrac);