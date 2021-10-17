#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;

private:
	const std::string ParseShader(const char* shaderPath);
	void CompileShaders(const char* vertexShader, const char* fragmentShader);
};