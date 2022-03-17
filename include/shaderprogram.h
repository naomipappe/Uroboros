#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <memory>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.h>
#include <texture.h>

//TODO Figure out the structure of the refactored engine model
// 1. What is a material? What constitutes the material?
// 2. What is a hierarchy of materials? Is there an inherent hierarchy?


namespace Uroboros {
    class ShaderProgram {
    public:
        ShaderProgram() = delete;
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram(Shader&& vertexShader, Shader&& fragmentShader) noexcept;
        ShaderProgram(std::unique_ptr<Shader> vertexShader, std::unique_ptr<Shader> fragmentShader);
        ~ShaderProgram();
        void use() const;

        void setUniform(const std::string& uniformName, int value);
        void setUniform(const std::string& uniformName, bool value);
        void setUniform(const std::string& uniformName, float value);
        void setUniform(const std::string& uniformName, const glm::vec3& value);
        void setUniform(const std::string& uniformName, const glm::mat3& value);
        void setUniform(const std::string& uniformName, const glm::mat4& value);

    private:
        uint32_t id;
        static constexpr uint16_t infoLogSize = 512;
        inline static const std::string cDiffuseSamplerName = "material.diffuse_map";
        inline static const std::string cSpecularSamplerName = "material.specular_map";
        inline static const std::string cNormalSamlerName = "material.normal_map";

    private:
        void createShaderProgram(uint32_t vertexShaderId, uint32_t fragmentShaderId);
    };
}// namespace Ouroboros
#endif