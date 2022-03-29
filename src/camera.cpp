#include <camera.h>

namespace Uroboros {
    Camera::Camera(const glm::vec3& aPosition, const glm::vec3& aFrontDirection, const glm::vec3& aUpDirection)
        : mWorldUp(glm::normalize(aUpDirection)),
          mPosition(aPosition),
          mFrontDirection(glm::normalize(aFrontDirection)),
          mUpDirection(glm::normalize(aUpDirection)) {
        mRightDirection = glm::normalize(glm::cross(mFrontDirection, mUpDirection));
    }

    Camera::Camera(const glm::vec3& cameraPos)
        : Camera(cameraPos,
                 glm::vec3(0.0f, 0.0f, -1.0f),
                 glm::vec3(0.0f, 1.0f, 0.0f)) {
    }

    glm::mat4 Camera::view() const {
        return glm::lookAt(mPosition, mPosition + mFrontDirection, mUpDirection);
    }

    glm::mat4 Camera::projection() const {
        return glm::perspective(glm::radians(mFov), mWidth / mHeight, cNear, cFar);
    }

    glm::vec3 Camera::position() const {
        return mPosition;
    }

    glm::vec3 Camera::direction() const {
        return mFrontDirection;
    }

    void Camera::setAspectRatio(float aWidth, float aHeight) {
        if (aWidth < 0 || aHeight < 0) {
            throw std::invalid_argument("Aspect ratio arguments should not be negative");
        }
        if (std::abs(aHeight) <= 1e-7f || std::abs(aWidth) <= 1e-7) {
            throw std::invalid_argument("Aspect ration arguments should not be zero");
        }
        mWidth = aWidth;
        mHeight = aHeight;
    }

    void Camera::keyboardInput(Camera::CameraMovement aDirection, float aDeltaTime) {
        switch (aDirection) {
            case CameraMovement::Forward:
                mPosition += (mMovementSpeed * aDeltaTime) * mFrontDirection;
                break;
            case CameraMovement::Backward:
                mPosition -= (mMovementSpeed * aDeltaTime) * mFrontDirection;
                break;
            case CameraMovement::Left:
                mPosition -= (mMovementSpeed * aDeltaTime) * mRightDirection;
                break;
            case CameraMovement::Right:
                mPosition += (mMovementSpeed * aDeltaTime) * mRightDirection;
                break;
        }
    }
    void Camera::mouseInput(float aXOffset, float aYOffset) {
        aXOffset *= mMouseSensitivity;
        aYOffset *= mMouseSensitivity;
        mYaw += aXOffset;
        mPitch += aYOffset;
        if (glm::abs(mPitch) > 89.0f) {
            mPitch = glm::sign(mPitch) * 89.0f;
        }
        updateCameraVectors();
    }

    void Camera::scrollInput(float aYOffset) {
        mFov -= aYOffset * 0.1f;
        if (mFov < 1.0f) {
            mFov = 1.0f;
        }
        if (mFov > 45.0f) {
            mFov = 45.0f;
        }
    }

    void Camera::updateCameraVectors() {
        mFrontDirection.x = glm::cos(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
        mFrontDirection.y = glm::sin(glm::radians(mPitch));
        mFrontDirection.z = glm::sin(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
        mFrontDirection = glm::normalize(mFrontDirection);
        mRightDirection = glm::normalize(glm::cross(mFrontDirection, mWorldUp));
        mUpDirection = glm::normalize(glm::cross(mRightDirection, mFrontDirection));
    }
}// namespace Ouroboros