#include "pch.h"
#include <cmath>
#include <glm/gtx/component_wise.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Camera.h"
#include "Ray.h"
#include "Image.h"
#include "Objects/Hittable.h"
#include "Objects/Sphere.h"
#include "Objects/Plane.h"
#include "Materials.h"
#include "Utility.h"


glm::vec3 rayColor(const Ray& ray, const HittableList& world, int depth)
{
	if (depth <= 0)
	{
		return glm::vec3(0.0);
	}

	HitRecord hit = world.hit(ray, 0.001, INFINITY);
	if (hit.collides)
	{
		assert(glm::dot(ray.direction, hit.normal) < 0.0f);
		auto [scatterRay, att] = hit.material->scatter(ray, hit);
		return att * rayColor(scatterRay, world, depth - 1);
	}
	float t = std::min(0.5f * (ray.direction.y + 1.0f), 1.0f);
	return (1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(1.0, 0.2, 1.0);
}

int main()
{
	//std::cout << glm::to_string(refract(glm::normalize(glm::vec3(1.0, -1.0, 0.0)), glm::vec3(0.0, -1.0, 0.0), std::sqrt(2) / 2.0f));
	//////////////////////////////////////////////////////////////////////////
	// Viewport stuff
	//////////////////////////////////////////////////////////////////////////
	const float aspectRatio = 16.0f / 9.0f;
	const int imgHeight = 360;
	const int imgWidth = aspectRatio * imgHeight;
	const int samplesPerPixel = 50;
	const int maxDepth = 50;

	Camera camera(glm::vec3(0.0, 0.5, 1.0), glm::vec3(0.0, 0.0, -1.0), aspectRatio, 110.0, 1.0);

	Image img(imgWidth, imgHeight);

	//////////////////////////////////////////////////////////////////////////
	// World stuff
	//////////////////////////////////////////////////////////////////////////
	auto matGround = std::make_shared<Lambertian>(glm::vec3(1.0));
	auto matCenter = std::make_shared<Lambertian>(glm::vec3(0.7, 0.3, 0.3));
	auto matLeft = std::make_shared<Dielectric>(1.52f);
	auto matRight = std::make_shared<Metal>(glm::vec3(0.8, 0.6, 0.2));

	HittableList world;
	world.add(std::make_shared<Plane>(glm::vec3(0.0, 1.0, 0.0), 0.0, matGround));
	world.add(std::make_shared<Sphere>(glm::vec3(0.0, 0.5, -1.0), 0.5, matCenter));
	world.add(std::make_shared<Sphere>(glm::vec3(-1.0, 0.5, -1.0), 0.5, matLeft));
	world.add(std::make_shared<Sphere>(glm::vec3(1.0, 0.5, -1.0), 0.5, matRight));

	for (float j = imgHeight - 1; j >= 0; --j)
	{
		std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (float i = 0; i < imgWidth; ++i)
		{
			glm::vec3 color(0.0);
			for (int s = 0; s < samplesPerPixel; ++s)
			{
				float u = (i + randFloat()) / imgWidth;
				float v = (j + randFloat()) / imgHeight;

				auto ray = camera.getRay(u, v);
				color += rayColor(ray, world, maxDepth);
			}
			img.writePixel(color, samplesPerPixel);
		}
	}
	img.writeImage("lmao.png");
	ShellExecute(0, L"open", L"lmao.png", 0, 0, SW_SHOW);

	return 0;
}