#include "pch.h"
#include "Image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <cmath>


Image::Image(int width, int height) :
	m_Width(width), m_Height(height)
{
	m_Img = std::make_unique<uint8_t[]>(width * height * 3);
	m_ImgPos = m_Img.get();
}

void Image::writePixel(const glm::vec3& color)
{
	*m_ImgPos++ = static_cast<uint8_t>(255 * color.x);
	*m_ImgPos++ = static_cast<uint8_t>(255 * color.y);
	*m_ImgPos++ = static_cast<uint8_t>(255 * color.z);
}

void Image::writePixel(const glm::vec3& color, int samplesPerPixel)
{
	float scale = 1.0f / samplesPerPixel;
	int r = 256 * std::sqrt(scale * color.r);
	int g = 256 * std::sqrt(scale * color.g);
	int b = 256 * std::sqrt(scale * color.b);
	*m_ImgPos++ = static_cast<uint8_t>(std::clamp(r, 0, 255));
	*m_ImgPos++ = static_cast<uint8_t>(std::clamp(g, 0, 255));
	*m_ImgPos++ = static_cast<uint8_t>(std::clamp(b, 0, 255));
}

void Image::writePixel(const glm::vec3& color, int samplesPerPixel, int pixelOffset)
{
	float scale = 1.0f / samplesPerPixel;
	int r = 256 * std::sqrt(scale * color.r);
	int g = 256 * std::sqrt(scale * color.g);
	int b = 256 * std::sqrt(scale * color.b);
	uint8_t* pos = m_Img.get() + 3 * pixelOffset;
	*pos++ = static_cast<uint8_t>(std::clamp(r, 0, 255));
	*pos++ = static_cast<uint8_t>(std::clamp(g, 0, 255));
	*pos++ = static_cast<uint8_t>(std::clamp(b, 0, 255));
}

void Image::writeImage(const std::string& fileName)
{
	stbi_write_png(fileName.c_str(), m_Width, m_Height, 3, m_Img.get(), m_Width * 3);
}

