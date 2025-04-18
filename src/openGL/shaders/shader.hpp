#pragma once

#include <glad/glad.h>
#include <optional>
#include <string>
#include <unordered_map>
#include "glm/fwd.hpp"

class Shader {
public:
    Shader() = default;
    ~Shader();

    void   use() const;
    GLuint get_ID() const;
    void   load_shader(const std::string& vertexPath, const std::string& fragmentPath);
    void   set_uniform_matrix_4fv(const std::string& name, const glm::mat4& value);
    void   set_uniform_vector_4f(const std::string& name, const glm::vec4& value);
    void   set_uniform_vector_3f(const std::string& name, const glm::vec3& value);
    void   set_uniform_3fv(const std::string& name, const glm::vec3& value);
    void   set_uniform_1f(const std::string& name, float value);
    void   set_uniform_1i(const std::string& name, int value);

private:
    GLuint                                 _programID;
    std::unordered_map<std::string, GLint> _uniform_cache;

    GLuint               compile_shader(const std::string& path, GLenum type);
    std::string          read_file(const std::string& path);
    std::optional<GLint> get_uniform_location(const std::string& name);
};
