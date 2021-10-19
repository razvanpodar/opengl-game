#include <iostream>
#include "GL/glew.h"
#include "vendor/stb_image/stb_image.h"

const int TEXTURE_COUNT = 16;

class TextureManager
{
public:
	unsigned int m_textures[TEXTURE_COUNT];
	int m_textureCount = 0;
	int m_width;
	int m_height;
	int m_channels;
	unsigned char* m_data;
public:
	//TextureManager(int textureCount);
	void LoadImage(const char* imagePath);
	void AddTexture(int type);
	void BindTexture(int index);
};