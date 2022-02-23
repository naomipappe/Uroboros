#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <memory>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.h>
#include <texture.h>

//TODO
// Figure out some common shader variable names
// Use them to generalize working with shaders
// 1. Set shader uniforms not by name, but by predefined methods
namespace Ouroboros {
    class ShaderProgram {
    public:
        ShaderProgram() = delete;
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram(Shader&& vertexShader, Shader&& fragmentShader) noexcept;
        ShaderProgram(std::unique_ptr<Shader> vertexShader, std::unique_ptr<Shader> fragmentShader);
        ~ShaderProgram();
        void use() const;

        void setUniform(const std::string& uniformName, const int& value);
        void setUniform(const std::string& uniformName, const bool& value);
        void setUniform(const std::string& uniformName, const float& value);
        void setUniform(const std::string& uniformName, const glm::vec3& value);
        void setUniform(const std::string& uniformName, const glm::mat3& value);
        void setUniform(const std::string& uniformName, const glm::mat4& value);

    private:
        unsigned int id;
        static const size_t infoLogSize = 512;
        static const std::string diffuseUniformName;
        static const std::string specularUniformName;

    private:
        void createShaderProgram(uint32_t vertexShaderId, uint32_t fragmentShaderId);
    };
}// namespace Ouroboros
#endif