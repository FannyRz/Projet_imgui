#include "shader.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include "glm/gtc/type_ptr.hpp"

void Shader::load_shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    GLuint vertexShader   = compile_shader(vertexPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = compile_shader(fragmentPath, GL_FRAGMENT_SHADER);
    _programID            = glCreateProgram();
    glAttachShader(_programID, vertexShader);
    glAttachShader(_programID, fragmentShader);
    glLinkProgram(_programID);

    GLint success{};
    glGetProgramiv(_programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(_programID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << '\n';
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(_programID);
}

void Shader::use() const
{
    glUseProgram(_programID);
}

GLuint Shader::get_ID() const
{
    return _programID;
}

GLuint Shader::compile_shader(const std::string& path, GLenum type)
{
    std::string sourceCode = read_file(path);
    const char* code       = sourceCode.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    GLint success{};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << infoLog << '\n';
    }

    return shader;
}

std::string Shader::read_file(const std::string& path)
{
    std::ifstream     file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// - Uniforms
void Shader::set_uniform_matrix_4fv(const std::string& name, const glm::mat4& value)
{
    std::optional<GLint> location = get_uniform_location(name);
    if (location.has_value())
        glUniformMatrix4fv(location.value(), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set_uniform_vector_4f(const std::string& name, const glm::vec4& value)
{
    std::optional<GLint> location = get_uniform_location(name);
    if (location.has_value())
        glUniform4fv(location.value(), 1, glm::value_ptr(value));
}

void Shader::set_uniform_vector_3f(const std::string& name, const glm::vec3& value)
{
    std::optional<GLint> location = get_uniform_location(name);
    if (location.has_value())
        glUniform4fv(location.value(), 1, glm::value_ptr(value));
}

void Shader::set_uniform_3fv(const std::string& name, const glm::vec3& value)
{
    std::optional<GLint> location = get_uniform_location(name);
    if (location.has_value())
        glUniform3fv(location.value(), 1, glm::value_ptr(value));
}

void Shader::set_uniform_1f(const std::string& name, const float value)
{
    std::optional<GLint> location = get_uniform_location(name);
    if (location.has_value())
        glUniform1f(location.value(), value);
}

void Shader::set_uniform_1i(const std::string& name, const int value)
{
    std::optional<GLint> location = get_uniform_location(name);
    if (location.has_value())
        glUniform1i(location.value(), value);
}

// - Uniform location
std::optional<GLint> Shader::get_uniform_location(const std::string& name)
{
    if (_uniform_cache.find(name) != _uniform_cache.end())
    {
        return _uniform_cache[name];
    }
    GLint location = glGetUniformLocation(_programID, name.c_str());
    if (location == -1)
    {
        // std::cerr << "Uniform " << name << " not found!" << std::endl;
        return std::nullopt;
    }
    _uniform_cache[name] = location;
    return location;
}
