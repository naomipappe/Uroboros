#ifndef ENTRYPOINT_CAMERA_H
#define ENTRYPOINT_CAMERA_H

#include <stdexcept>

#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    enum class CameraMovement { Forward,
                                Backward,
                                Left,
                                Right };

    Camera();
    explicit Camera(const glm::vec3 &cameraPos);
    Camera(const glm::vec3 &cameraPos, const glm::vec3 &cameraFront, const glm::vec3 &cameraUp);
    Camera(const glm::vec3 &cameraPos, const glm::vec3 &cameraFront, const glm::vec3 &cameraUp,
           float yaw, float pitch);

    [[nodiscard]] glm::mat4 view() const;
    [[nodiscard]] glm::mat4 projection() const;
    [[nodiscard]] glm::vec3 position() const;
    [[maybe_unused, nodiscard]] glm::vec3 direction() const;

    void setAspectRatio(float width, float height);

    void keyboardInput(CameraMovement direction, float timeDelta);
    void mouseInput(float xOffset, float yOffset);
    void scrollInput(float yOffset);

private:
    const glm::vec3 worldUp;
    static constexpr float near = 0.1f;
    static constexpr float far = 100.f;

    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_frontDirection = glm::vec3(0.0, 0.0, -1.0);
    glm::vec3 m_upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_rightDirection;

    float m_width = 800.0f;
    float m_height = 600.0f;

    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    float m_movementSpeed = 5.5f;
    float m_mouseSensitivity = 0.01f;
    float m_fov = 45.0f;

private:
    void updateCameraVectors();
};

#endif//ENTRYPOINT_CAMERA_H
