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

void Shader::SetUniform1i(const std::string& name, int value) const
{
    unsigned int location = glGetUniformLocation(m_sProgramID, name.c_str());
    glUniform1i(location, value);
}

void Shader::SetUniform1f(const std::string& name, float value) const
{
    unsigned int location = glGetUniformLocation(m_sProgramID, name.c_str());
    glUniform1f(location, value);
}

void Shader::SetUniform3f(const std::string& name, float f1, float f2, float f3) const
{
    unsigned int location = glGetUniformLocation(m_sProgramID, name.c_str());
    glUniform3f(location, f1, f2, f3);
}

void Shader::SetUniform3fv(const std::string& name, glm::vec3 value)
{
    unsigned int location = glGetUniformLocation(m_sProgramID, name.c_str());
    glUniform3fv(location, 1, glm::value_ptr(value));
}
void Shader::SetUniform4fv(const std::string& name, glm::vec4 value)
{
    unsigned int location = glGetUniformLocation(m_sProgramID, name.c_str());
    glUniform4fv(location, 1, glm::value_ptr(value));
}
void Shader::SetUniformMatrix3fv(const std::string& name, glm::mat3 value)
{
    unsigned int location = glGetUniformLocation(m_sProgramID, name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::SetUniformMatrix4fv(const std::string& name, glm::mat4 value)
{
    unsigned int location = glGetUniformLocation(m_sProgramID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
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


