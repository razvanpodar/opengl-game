#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexSource = ParseShader(vertexPath);
    std::string fragmentSource = ParseShader(fragmentPath);

    CompileShaders(vertexSource.c_str(), fragmentSource.c_str());
}

void Shader::Use()
{
    glUseProgram(m_sProgramID);
}

void Shader::Delete()
{
    glDeleteProgram(m_sProgramID);
}

void Shader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_sProgramID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_sProgramID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_sProgramID, name.c_str()), value);
}

const std::string Shader::ParseShader(const char* shaderPath)
{
    std::string shaderSource;
    std::ifstream shaderFile;

    // ensure ifstream objects can throw exceptions:
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        // read file's buffer contents into streams
        shaderStream << shaderFile.rdbuf();
        // close file handlers
        shaderFile.close();
        // convert stream into string
        shaderSource = shaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    //const char* shaderCode = shaderSource.c_str();
    return shaderSource;
}

void Shader::CompileShaders(const char* vertexShader, const char* fragmentShader)
{
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShader, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShader, NULL);
    glCompileShader(fragment);
    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    
    // TODO: Move shader linking to another method or inside the constructor

    // Shader program
    m_sProgramID = glCreateProgram();
    glAttachShader(m_sProgramID, vertex);
    glAttachShader(m_sProgramID, fragment);
    glLinkProgram(m_sProgramID);
    // print linking errors if any
    glGetProgramiv(m_sProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_sProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}


