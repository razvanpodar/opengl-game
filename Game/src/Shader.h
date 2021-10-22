#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"

class Shader
{
public:
	unsigned int m_sProgramID;

public:
	Shader(const char* vertexPath, const char* fragmentPath);
	
	// Use shader program
	void Use();
	void Delete();
	// Set uniforms
	void SetUniform1i(const std::string& name, int value) const;
	void SetUniform1f(const std::string& name, float value) const;
	void SetUniform3f(const std::string& name, float f1, float f2, float f3) const;
	void SetUniform3fv(const std::string& name, glm::vec3 value);
	void SetUniform4fv(const std::string& name, glm::vec4 value);
	void SetUniformMatrix3fv(const std::string& name, glm::mat3 value);
	void SetUniformMatrix4fv(const std::string& name, glm::mat4 value);

private:
	const std::string ParseShader(const char* shaderPath);
	void CompileShaders(const char* vertexShader, const char* fragmentShader);
};