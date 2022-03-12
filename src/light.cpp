#include <light.h>
namespace Uroboros {
    uint8_t PointLight::counter = 0;

    Light::Light(std::shared_ptr<ShaderProgram> aShader) {
        mShader = std::move(aShader);
    }

    DirectionalLight::DirectionalLight(const std::shared_ptr<ShaderProgram>& aShader, const glm::vec3& aDirection)
        : Light(aShader),
          mDirection(aDirection) {
        mShader->use();

        mShader->setUniform(cDirectionUniformName, mDirection);
        mShader->setUniform(cAmbientUniformName, mAmbient);
        mShader->setUniform(cDiffuseUniformName, mDiffuse);
        mShader->setUniform(cSpecularUniformName, mSpecular);
    }

    const glm::vec3& DirectionalLight::getDirection() const {
        return mDirection;
    }

    void DirectionalLight::setDirection(const glm::vec3& aDirection) {
        mShader->setUniform(cDirectionUniformName, aDirection);
        mDirection = aDirection;
    }

    void DirectionalLight::setAmbient(const glm::vec3& aAmbientColor) {
        mShader->setUniform(cAmbientUniformName, aAmbientColor);
        mAmbient = aAmbientColor;
    }

    void DirectionalLight::setDiffuse(const glm::vec3& aDiffuseColor) {
        mShader->setUniform(cDiffuseUniformName, aDiffuseColor);
        mDiffuse = aDiffuseColor;
    }

    void DirectionalLight::setSpecular(const glm::vec3& aSpecularColor) {
        mShader->setUniform(cSpecularUniformName, aSpecularColor);
        mSpecular = aSpecularColor;
    }

    PointLight::PointLight(const std::shared_ptr<ShaderProgram>& aShader, const glm::vec3& aPosition)
        : Light(aShader),
          mPosition(aPosition),
          mIndex(std::to_string(counter)) {
        ++counter;
        mShader->use();

        mPositionUniformName = "pointLights[" + mIndex + "].position";
        mAmbientUniformName = "pointLights[" + mIndex + "].ambient";
        mDiffuseUniformName = "pointLights[" + mIndex + "].diffuse";
        mSpecularUniformName = "pointLights[" + mIndex + "].specular";

        mShader->setUniform(mPositionUniformName, aPosition);
        mShader->setUniform(mAmbientUniformName, mAmbient);
        mShader->setUniform(mDiffuseUniformName, mDiffuse);
        mShader->setUniform(mSpecularUniformName, mSpecular);

        mShader->setUniform("pointLights[" + mIndex + "].constant", cConstant);
        mShader->setUniform("pointLights[" + mIndex + "].linear", cLinear);
        mShader->setUniform("pointLights[" + mIndex + "].quadratic", cQuadratic);
    }

    const glm::vec3& PointLight::getPosition() const {
        return mPosition;
    }

    void PointLight::setPosition(const glm::vec3& aPosition) {
        mShader->use();
        mShader->setUniform(mPositionUniformName, aPosition);
        mPosition = aPosition;
    }

    void PointLight::setAmbient(const glm::vec3& aAmbientColor) {
        mShader->use();
        mShader->setUniform(mAmbientUniformName, aAmbientColor);
        mAmbient = aAmbientColor;
    }

    void PointLight::setDiffuse(const glm::vec3& aDiffuseColor) {
        mShader->use();
        mShader->setUniform(mDiffuseUniformName, aDiffuseColor);
        mDiffuse = aDiffuseColor;
    }

    void PointLight::setSpecular(const glm::vec3& aSpecularColor) {
        mShader->use();
        mShader->setUniform(mSpecularUniformName, aSpecularColor);
        mSpecular = aSpecularColor;
    }

    Spotlight::Spotlight(const std::shared_ptr<ShaderProgram>& aShader, const glm::vec3& aPosition, const glm::vec3& aDirection) {
        mShader = aShader;
        mPosition = aPosition;
        mDirection = aDirection;

        mShader->use();
        mShader->setUniform(cDirectionUniformName, mDirection);
        mShader->setUniform(cPositionUniformName, mPosition);

        mShader->setUniform(cAmbientUniformName, mAmbient);
        mShader->setUniform(cDiffuseUniformName, mDiffuse);
        mShader->setUniform(cSpecularUniformName, mSpecular);

        mShader->setUniform("spotLight.constant", cConstant);
        mShader->setUniform("spotLight.linear", cLinear);
        mShader->setUniform("spotLight.quadratic", cQuadratic);
        mShader->setUniform("spotLight.cutOff", cCutOff);
        mShader->setUniform("spotLight.outerCutOff", cOuterCutOff);
    }

    const glm::vec3& Spotlight::getDirection() const {
        return mDirection;
    }

    void Spotlight::setDirection(const glm::vec3& aDirection) {
        mShader->use();
        mShader->setUniform(cDirectionUniformName, aDirection);
        mDirection = aDirection;
    }

    void Spotlight::setAmbient(const glm::vec3& aAmbientColor) {
        mShader->use();
        mShader->setUniform(cAmbientUniformName, aAmbientColor);
        mAmbient = aAmbientColor;
    }

    void Spotlight::setDiffuse(const glm::vec3& aDiffuseColor) {
        mShader->use();
        mShader->setUniform(cDiffuseUniformName, aDiffuseColor);
        mDiffuse = aDiffuseColor;
    }

    void Spotlight::setSpecular(const glm::vec3& aSpecularColor) {
        mShader->use();
        mShader->setUniform(cSpecularUniformName, aSpecularColor);
        mSpecular = aSpecularColor;
    }
}// namespace Uroboros
