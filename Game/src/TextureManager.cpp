#include "TextureManager.h"

void TextureManager::LoadImage(const char* imagePath, const char* directoryPath)
{
    std::string path = std::string(directoryPath) + "/" + std::string(imagePath);
	stbi_set_flip_vertically_on_load(true);
	m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 0);
}

int TextureManager::AddTexture(std::string type, std::string path)
{
    if (m_textureCount > TEXTURE_COUNT || m_textureCount < 0)
    {
        std::cout << "TEXTURE::MANAGER::Max texture count was exceeded!" << std::endl;
        return -1;
    }
    else
    {
        glGenTextures(1, &m_textures[m_textureCount].id);
        glBindTexture(GL_TEXTURE_2D, m_textures[m_textureCount].id);

        // Set wrapping type
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Set filtering type
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (m_data)
        {
            m_textures[m_textureCount].type = type;
            m_textures[m_textureCount].path = path;
            // Generate texture
            if (m_channels == 3) // for jpg
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else if (m_channels == 4) // for png
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

        // Return the index of the texture that was added
        return m_textureCount++;
    }
}

void TextureManager::BindTexture(int index)
{
    if (index < 0 || index >= TEXTURE_COUNT)
    {
        std::cout << "TEXTURE::MANAGER::The index " << index 
            << " is not in range! (0, " << TEXTURE_COUNT - 1 << ")" << std::endl;
    }
    else
    {
        if (m_textures[index].id == 0)
        {
            std::cout << "TEXTURE::MANAGER::There is no texture at index " 
                << index << std::endl;
            return;
        }
        glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_2D, m_textures[index].id);
    }
}