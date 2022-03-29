#ifndef ENTRYPOINT_CAMERA_H
#define ENTRYPOINT_CAMERA_H

#include <stdexcept>

#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Uroboros {
    class Camera {
    public:
        enum class CameraMovement { Forward,
                                    Backward,
                                    Left,
                                    Right };

        Camera() = default;
        explicit Camera(const glm::vec3 &cameraPos);

        Camera(const glm::vec3 &aPosition, const glm::vec3 &aFrontDirection, const glm::vec3 &aUpDirection);

        [[nodiscard]] glm::mat4 view() const;
        [[nodiscard]] glm::mat4 projection() const;
        [[nodiscard]] glm::vec3 position() const;
        [[maybe_unused, nodiscard]] glm::vec3 direction() const;

        void setAspectRatio(float aWidth, float aHeight);

        void keyboardInput(CameraMovement aDirection, float aDeltaTime);
        void mouseInput(float aXOffset, float aYOffset);
        void scrollInput(float aYOffset);

    private:
        const glm::vec3 mWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        static constexpr float cNear = 0.1f;
        static constexpr float cFar = 100.f;

        glm::vec3 mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 mFrontDirection = glm::vec3(0.0, 0.0, -1.0);
        glm::vec3 mUpDirection = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 mRightDirection = glm::normalize(glm::cross(mFrontDirection, mUpDirection));

        float mWidth = 800.0f;
        float mHeight = 600.0f;

        float mYaw = -90.0f;
        float mPitch = 0.0f;
        float mMovementSpeed = 5.5f;
        float mMouseSensitivity = 0.1f;
        float mFov = 45.0f;

    private:
        void updateCameraVectors();
    };
}// namespace Ouroboros
#endif//ENTRYPOINT_CAMERA_H
