#ifndef ENTRYPOINT_LIGHT_H
#define ENTRYPOINT_LIGHT_H
#include <memory>
#include <utility>

#include <glm/glm.hpp>

#include <shaderprogram.h>
#include <camera.h>
namespace Uroboros {
    class Light {
    public:
        Light() = delete;
        void setAmbient(glm::vec3 ambient) {
            m_ambient = ambient;
            m_shader->setUniform("light.ambient", m_ambient);
        };
        void setDiffuse(glm::vec3 diffuse) {
            m_diffuse = diffuse;
            m_shader->setUniform("light.diffuse", m_diffuse);
        };
        void setSpecular(glm::vec3 specular) {
            m_specular = specular;
            m_shader->setUniform("light.specular", m_specular);
        };

    protected:
        explicit Light(std::shared_ptr<ShaderProgram> shader);
        Light(const Light& other) = default;
        Light(Light&& other) = default;

    protected:
        glm::vec3 m_ambient = glm::vec3(0.2f);
        glm::vec3 m_diffuse = glm::vec3(0.5f);
        glm::vec3 m_specular = glm::vec3(1.0f);
        std::shared_ptr<ShaderProgram> m_shader;
    };
    class DirectionalLight : public Light {
    public:
        DirectionalLight(std::shared_ptr<ShaderProgram> shader, const glm::vec3& direction);
        [[nodiscard, maybe_unused]] glm::vec3 direction() const;

    private:
        glm::vec3 m_direction;
    };
    class PointLight : public Light {
    public:
        PointLight(std::shared_ptr<ShaderProgram> shader, const glm::vec3& position);
        [[nodiscard, maybe_unused]] glm::vec3 position() const;

    private:
        glm::vec3 m_position;
        float m_constant = 1.0f;
        float m_linear = 0.045f;
        float m_quadratic = 0.0075f;
    };
    class Spotlight : public Light {
    public:
        Spotlight(std::shared_ptr<ShaderProgram> shader, const glm::vec3& position, const glm::vec3& direction);
        [[nodiscard, maybe_unused]] glm::vec3 position() const;
        [[nodiscard, maybe_unused]] glm::vec3 direction() const;
        void setPosition(const glm::vec3& position);
        void setDirection(const glm::vec3& direction);

    private:
        glm::vec3 m_position;
        glm::vec3 m_direction;
        float m_cutoff = glm::radians(12.5f);
        float m_outercutoff = glm::radians(17.5f);
        float m_constant = 1.0f;
        float m_linear = 0.007f;
        float m_quadratic = 0.0002f;
    };
}// namespace Ouroboros
#endif//ENTRYPOINT_LIGHT_H
