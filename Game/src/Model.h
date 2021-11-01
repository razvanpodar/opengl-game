#pragma once

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

class Model
{
private:
	std::vector<Mesh> m_meshes;
	std::string m_directory;
	TextureManager m_texManager;
public:
	Model(const char* path);
	void Draw(Shader& shader);
private:
	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<int> LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);
};