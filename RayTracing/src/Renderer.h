#pragma once

#include <atomic>

#include "Ray.h"
#include "Objects/Hittable.h"
#include "Camera.h"
#include "Image.h"

class Renderer
{
public:
	Renderer() = default;
	Renderer(int width, int height, Camera& camera, HittableList& world);

	void render();

private:
	glm::vec3 rayColor(const Ray& ray, const HittableList& world, int depth);
	void startWorker(int startPixelOffset, int rows);

private:
	std::atomic<int> m_FinishedRows = 0;
	int m_Width;
	int m_Height;
	int m_SamplesPerPixel = 50;
	int m_MaxDepth = 50;
	Camera& m_Camera;
	HittableList& m_World;
	Image m_Image;
};

