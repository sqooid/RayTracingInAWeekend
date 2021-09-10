#include "pch.h"
#include <cmath>

#include "Camera.h"
#include "Ray.h"
#include "Image.h"
#include "Objects/Hittable.h"
#include "Objects/Sphere.h"
#include "Utility.h"


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
	const int imgHeight = 360;
	const int imgWidth = aspectRatio * imgHeight;
	const int samplesPerPixel = 50;

	Camera camera(glm::vec3(0.0), glm::vec3(0.0, 0.0, -1.0), aspectRatio, 110.0, 1.0);

	Image img(imgWidth, imgHeight);

	//////////////////////////////////////////////////////////////////////////
	// World stuff
	//////////////////////////////////////////////////////////////////////////
	HittableList world;
	world.add(std::make_shared<Sphere>(glm::vec3(1.0, 2.0, -5.0), 1.0));
	world.add(std::make_shared<Sphere>(glm::vec3(0.0, -110.0, 0.0), 100.0));

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
				color += rayColor(ray, world);
			}
			img.writePixel(color, samplesPerPixel);
		}
	}
	img.writeImage("lmao.png");
	ShellExecute(0, L"open", L"lmao.png", 0, 0, SW_SHOW);

	return 0;
}