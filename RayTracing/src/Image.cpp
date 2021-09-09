#include "pch.h"
#include "Image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>


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

void Image::writeImage(const std::string& fileName)
{
	stbi_write_png(fileName.c_str(), m_Width, m_Height, 3, m_Img.get(), m_Width * 3);
}

