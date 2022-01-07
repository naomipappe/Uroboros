#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <memory>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>
#include <Texture.h>


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

    void setDiffuseMap(const std::shared_ptr<Texture>& value);
    void setSpecularMap(const std::shared_ptr<Texture>& value);
    void setShininess(const std::shared_ptr<Texture>& value);

private:
    unsigned int id;
    static const size_t infoLogSize = 512;
    static const std::string diffuseUniformName;
    static const std::string specularUniformName;

private:
    void createShaderProgram(uint32_t vertexShaderId, uint32_t fragmentShaderId);
};

#endif