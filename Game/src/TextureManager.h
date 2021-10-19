#pragma once
#include <iostream>
#include "GL/glew.h"
#include "vendor/stb_image/stb_image.h"

// This can be replaced with the gl constant 
// GL_MAX_TEXTURE_IMAGE_UNITS that returns the max texture units count 
// but for testing purposes I just used a constant
const int TEXTURE_COUNT = 16;

class TextureManager
{
private:
	unsigned int m_textures[TEXTURE_COUNT];
	int m_textureCount = 0;
	int m_width;
	int m_height;
	int m_channels;
	unsigned char* m_data;
public:
	void LoadImage(const char* imagePath);
	void AddTexture(int type);
	void BindTexture(int index);
};