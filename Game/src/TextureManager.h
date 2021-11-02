#pragma once

#include <iostream>
#include "GL/glew.h"
#include "vendor/stb_image/stb_image.h"

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};

// This can be replaced with the gl constant 
// GL_MAX_TEXTURE_IMAGE_UNITS that returns the max texture units count 
// but for testing purposes I just used a constant
const int TEXTURE_COUNT = 16;

class TextureManager
{
private:
	// Change to vector of struct Texture
	Texture m_textures[TEXTURE_COUNT];
	int m_textureCount = 0;
	int m_width;
	int m_height;
	int m_channels;
	unsigned char* m_data;
public:
	std::string GetTextureType(int index)
	{
		return m_textures[index].type;
	}
	unsigned int GetTextureId(int index)
	{
		return m_textures[index].id;
	}
	void LoadImage(const char* imagePath, const char* directoryPath);
	int AddTexture(const std::string type, const std::string path);
	void BindTexture(int index);
};