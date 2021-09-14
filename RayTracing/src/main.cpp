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
#include "Renderer.h"

int main()
{
	//////////////////////////////////////////////////////////////////////////
	// Viewport stuff
	//////////////////////////////////////////////////////////////////////////
	const float aspectRatio = 16.0f / 9.0f;
	const int imgHeight = 360;
	const int imgWidth = aspectRatio * imgHeight;
	const int samplesPerPixel = 50;
	const int maxDepth = 50;

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

	//////////////////////////////////////////////////////////////////////////
	// Rendering
	//////////////////////////////////////////////////////////////////////////
	Camera camera(glm::vec3(0.0, 0.5, 1.0), glm::vec3(0.0, 0.0, -1.0), aspectRatio, 110.0, 1.0);
	Renderer renderer(imgWidth, imgHeight, camera, world);
	renderer.render();

	ShellExecute(0, L"open", L"lmao.png", 0, 0, SW_SHOW);

	return 0;
}