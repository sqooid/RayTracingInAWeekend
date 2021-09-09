#include "pch.h"
#include <cmath>

#include "Ray.h"
#include "Image.h"
#include "Objects/Hittable.h"
#include "Objects/Sphere.h"


glm::vec3 rayColor(const Ray& ray, const HittableList& world)
{
	HitRecord hit = world.hit(ray, 0, INFINITY);
	if (hit.collides)
	{
		return 0.5f * (hit.normal + glm::vec3(1.0));
	}
	return glm::vec3(0.5, 0.7, 1.0);
}

int main()
{
	//////////////////////////////////////////////////////////////////////////
	// Viewport stuff
	//////////////////////////////////////////////////////////////////////////
	const float aspectRatio = 16.0f / 9.0f;
	const int imgHeight = 1080;
	const int imgWidth = aspectRatio * imgHeight;

	glm::vec3 origin(0.0f);
	const float clipDistance = 1.0f;
	const float clipHeight = 2.0f;
	const float clipWidth = clipHeight * aspectRatio;
	const glm::vec3 clipCorner(-clipWidth / 2, -clipHeight / 2, clipDistance);

	Image img(imgWidth, imgHeight);

	//////////////////////////////////////////////////////////////////////////
	// World stuff
	//////////////////////////////////////////////////////////////////////////
	HittableList world;
	world.add(std::make_shared<Sphere>(glm::vec3(1.0, 2.0, 5.0), 1.0));
	world.add(std::make_shared<Sphere>(glm::vec3(0.0, -110.0, 0.0), 100.0));

	for (float j = imgHeight - 1; j >= 0; --j)
	{
		std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (float i = 0; i < imgWidth; ++i)
		{
			float u = i / (imgWidth - 1);
			float v = j / (imgHeight - 1);

			const glm::vec3 offset(u * clipWidth, v * clipHeight, 0.0f);
			Ray ray(origin, glm::normalize(clipCorner + offset - origin));
			auto color = rayColor(ray, world);
			img.writePixel(color);
		}
	}

	img.writeImage("lmao.png");
	ShellExecute(0, L"open", L"lmao.png", 0, 0, SW_SHOW);

	return 0;
}