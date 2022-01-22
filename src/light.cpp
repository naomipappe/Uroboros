#include <light.h>
namespace Ouroboros {

    Light::Light(std::shared_ptr<ShaderProgram> shader) {
        m_shader = std::move(shader);
        m_shader->setUniform("light.ambient", m_ambient);
        m_shader->setUniform("light.diffuse", m_diffuse);
        m_shader->setUniform("light.specular", m_specular);
    }

    DirectionalLight::DirectionalLight(std::shared_ptr<ShaderProgram> shader, const glm::vec3& direction)
        : Light(std::move(shader)),
          m_direction(direction) {
        m_shader->use();
        m_shader->setUniform("light.direction", m_direction);
    }

    glm::vec3 DirectionalLight::direction() const {
        return m_direction;
    }

    PointLight::PointLight(std::shared_ptr<ShaderProgram> shader, const glm::vec3& position)
        : Light(std::move(shader)),
          m_position(position) {
        m_shader->use();
        m_shader->setUniform("light.constant", m_constant);
        m_shader->setUniform("light.position", m_position);
        m_shader->setUniform("light.linear", m_linear);
        m_shader->setUniform("light.quadratic", m_quadratic);
    }
    glm::vec3 PointLight::position() const {
        return m_position;
    }

    Spotlight::Spotlight(std::shared_ptr<ShaderProgram> shader, const glm::vec3& position, const glm::vec3& direction)
        : Light(std::move(shader)),
          m_position(position),
          m_direction(direction) {
        m_shader->use();
        m_shader->setUniform("light.position", m_position);
        m_shader->setUniform("light.direction", m_direction);
        m_shader->setUniform("light.cutoff_cosine", glm::cos(m_cutoff));
        m_shader->setUniform("light.outer_cutoff_cosine", glm::cos(m_outercutoff));
        m_shader->setUniform("light.constant", m_constant);
        m_shader->setUniform("light.linear", m_linear);
        m_shader->setUniform("light.quadratic", m_quadratic);
    }
    glm::vec3 Spotlight::position() const {
        return m_position;
    }
    glm::vec3 Spotlight::direction() const {
        return m_direction;
    }
    void Spotlight::setPosition(const glm::vec3& position) {
        m_position = position;
        m_shader->setUniform("light.position", m_position);
    }
    void Spotlight::setDirection(const glm::vec3& direction) {
        m_direction = direction;
        m_shader->setUniform("light.direction", m_direction);
    }
}// namespace Ouroboros
