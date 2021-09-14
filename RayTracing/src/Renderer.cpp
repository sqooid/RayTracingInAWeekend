#include "pch.h"
#include "Renderer.h"

#include "Utility.h"
#include "Materials.h"

Renderer::Renderer(int width, int height, Camera& camera, HittableList& world) :
	m_Width(width), m_Height(height), m_Camera(camera), m_World(world), m_Image(width, height)
{

}

void Renderer::startWorker(int startPixelOffset, int rows)
{
	const int topOffset = startPixelOffset / m_Width;
	const int bottomOffset = m_Height - topOffset;
	for (float j = rows - 1; j >= 0; --j)
	{
		for (float i = 0; i < m_Width; ++i)
		{
			glm::vec3 color(0.0);
			for (int s = 0; s < m_SamplesPerPixel; ++s)
			{
				float u = (i + randFloat()) / m_Width;
				float v = (bottomOffset + j + randFloat()) / m_Height;

				auto ray = m_Camera.getRay(u, v);
				color += rayColor(ray, m_World, m_MaxDepth);
			}
			m_Image.writePixel(color, m_SamplesPerPixel, startPixelOffset + (rows - 1 - j) * m_Width + i);
		}
		++m_FinishedRows;
	}
}

glm::vec3 Renderer::rayColor(const Ray& ray, const HittableList& world, int depth)
{
	if (depth <= 0)
	{
		return glm::vec3(0.0);
	}

	HitRecord hit = world.hit(ray, 0.001, INFINITY);
	if (hit.collides)
	{
		auto [scatterRay, att] = hit.material->scatter(ray, hit);
		return att * rayColor(scatterRay, world, depth - 1);
	}
	float t = std::min(0.5f * (ray.direction.y + 1.0f), 1.0f);
	return (1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(1.0, 0.2, 1.0);	// This is the sky color
}

void Renderer::render()
{
	// Split image into row chunks
	int procCount = std::thread::hardware_concurrency() - 1;
	procCount = procCount ? procCount : 7;
	int chunkHeight = m_Height / procCount;
	int chunkLeftover = m_Height % procCount;
	// Start threads
	std::vector<std::thread> threadPool;
	for (int i = 0; i < procCount; ++i)
	{
		threadPool.emplace_back(std::thread(&Renderer::startWorker, this, chunkHeight * m_Width * i, i == procCount - 1 ? chunkHeight + chunkLeftover : chunkHeight));
	}
	// Check progress
	const int progressResolution = 20;	// Resolution of progress bar

	std::cout << "Rendering...\n";
	while (m_FinishedRows < m_Height)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		int progress = progressResolution * m_FinishedRows / m_Height;
		std::cout << "\r<";
		for (int i = 0; i < progressResolution; ++i)
		{
			if (i < progress)
			{
				std::cout << "-";
			}
			else
			{
				std::cout << " ";
			}
		}
		std::cout << ">" << std::flush;
	}
	for (auto& thread : threadPool)
	{
		thread.join();
	}
	m_Image.writeImage("lmao.png");
}
