#include <camera.h>

namespace Uroboros {
    Camera::Camera(const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp) : worldUp(cameraUp),
                                                                                                          m_position(cameraPos),
                                                                                                          m_frontDirection(cameraFront),
                                                                                                          m_upDirection(cameraUp),
                                                                                                          m_rightDirection() {
        m_rightDirection = glm::normalize(glm::cross(m_frontDirection, m_upDirection));
    }
    Camera::Camera()
        : Camera(glm::vec3(0.0f, 0.0f, 0.0f),
                 glm::vec3(0.0f, 0.0f, -1.0f),
                 glm::vec3(0.0f, 1.0f, 0.0f)) {
    }
    Camera::Camera(const glm::vec3& cameraPos)
        : Camera(cameraPos,
                 glm::vec3(0.0f, 0.0f, -1.0f),
                 glm::vec3(0.0f, 1.0f, 0.0f)) {
    }

    Camera::Camera(const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp, float yaw, float pitch)
        : Camera(cameraPos, cameraFront, cameraUp) {
        m_yaw = yaw;
        m_pitch = pitch;
    }

    glm::mat4 Camera::view() const {
        return glm::lookAt(m_position, m_position + m_frontDirection, m_upDirection);
    }

    glm::mat4 Camera::projection() const {
        return glm::perspective(glm::radians(m_fov), m_width / m_height, near, far);
    }

    glm::vec3 Camera::position() const {
        return m_position;
    }

    glm::vec3 Camera::direction() const {
        return m_frontDirection;
    }

    void Camera::setAspectRatio(float width, float height) {
        if (width < 0 || height < 0) {
            throw std::invalid_argument("Aspect ratio arguments should not be negative");
        }
        if (std::abs(height) <= 1e-7f || std::abs(width) <= 1e-7) {
            throw std::invalid_argument("Aspect ration arguments should not be zero");
        }
        m_width = width;
        m_height = height;
    }

    void Camera::keyboardInput(Camera::CameraMovement direction, float timeDelta) {
        switch (direction) {
            case CameraMovement::Forward:
                m_position += (m_movementSpeed * timeDelta) * m_frontDirection;
                break;
            case CameraMovement::Backward:
                m_position -= (m_movementSpeed * timeDelta) * m_frontDirection;
                break;
            case CameraMovement::Left:
                m_position -= (m_movementSpeed * timeDelta) * m_rightDirection;
                break;
            case CameraMovement::Right:
                m_position += (m_movementSpeed * timeDelta) * m_rightDirection;
                break;
        }
    }
    void Camera::mouseInput(float xOffset, float yOffset) {
        xOffset *= m_mouseSensitivity;
        yOffset *= m_mouseSensitivity;
        m_yaw += xOffset;
        m_pitch += yOffset;
        if (glm::abs(m_pitch) > 89.0f) {
            m_pitch = glm::sign(m_pitch) * 89.0f;
        }
        updateCameraVectors();
    }
    void Camera::scrollInput(float yOffset) {
        m_fov -= yOffset * 0.1f;
        if (m_fov < 1.0f) {
            m_fov = 1.0f;
        }
        if (m_fov > 45.0f) {
            m_fov = 45.0f;
        }
    }

    void Camera::updateCameraVectors() {
        m_frontDirection.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
        m_frontDirection.y = glm::sin(glm::radians(m_pitch));
        m_frontDirection.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
        m_frontDirection = glm::normalize(m_frontDirection);
        m_rightDirection = glm::normalize(glm::cross(m_frontDirection, worldUp));
        m_upDirection = glm::normalize(glm::cross(m_rightDirection, m_frontDirection));
    }
}// namespace Ouroboros