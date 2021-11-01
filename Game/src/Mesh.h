#pragma once

#include <string>
#include <vector>

#include "vendor/glm/glm.hpp"
#include "Shader.h"
#include "TextureManager.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

class Mesh
{
public:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<int> m_textures;
private:
	unsigned int VAO, VBO, EBO;

public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
		std::vector<int> textures);
	void Draw(Shader& shader, TextureManager& texManager);
private:
	void SetupMesh();
};