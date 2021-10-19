#include "TextureManager.h"

void TextureManager::LoadImage(const char* imagePath)
{
	stbi_set_flip_vertically_on_load(true);
	m_data = stbi_load(imagePath, &m_width, &m_height, &m_channels, 0);
}

void TextureManager::AddTexture(int type)
{
    glGenTextures(1, &m_textures[m_textureCount]);
    glBindTexture(GL_TEXTURE_2D, m_textures[m_textureCount]);

    // Set wrapping type
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set filtering type
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (m_data)
    {
        // Generate texture
        if (type == 0) // for jpg
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else if (type == 1) // for png
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        stbi_image_free(m_data);
    }
    else
    {
        std::cout << "TEXTURE::MANAGER::No image loaded!" << std::endl;
    }

    m_textureCount++;
}

void TextureManager::BindTexture(int index)
{
    if (m_textures[index] == 0)
        std::cout << "There is no texture at that index!" << std::endl;
    //glActiveTexture(index);
    if (index == 0)
        glActiveTexture(GL_TEXTURE0);
    if (index == 1)
        glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_textures[index]);
}