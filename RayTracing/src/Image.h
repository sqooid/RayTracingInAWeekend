#pragma once

#include <glm/glm.hpp>
#include <string>
#include <memory>
class Image
{
public:
	Image() = default;
	Image(int width, int height);

	void writePixel(const glm::vec3& color);
	void writeImage(const std::string& fileName);

private:
	std::unique_ptr<uint8_t[]> m_Img;
	uint8_t* m_ImgPos;
	int m_Width;
	int m_Height;
};

