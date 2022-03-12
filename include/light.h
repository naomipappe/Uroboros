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
        virtual void setAmbient(const glm::vec3& aAmbientColor) = 0;
        virtual void setDiffuse(const glm::vec3& aDiffuseColor) = 0;
        virtual void setSpecular(const glm::vec3& aSpecularColor) = 0;

        virtual ~Light() = default;

    protected:
        Light() = default;
        explicit Light(std::shared_ptr<ShaderProgram> shader);
        Light(const Light& other) = default;
        Light(Light&& other) = default;

    protected:
        //TODO Do I really need to store the shader pointer here?
        std::shared_ptr<ShaderProgram> mShader;
        glm::vec3 mAmbient = glm::vec3(0.2f);
        glm::vec3 mDiffuse = glm::vec3(0.5f);
        glm::vec3 mSpecular = glm::vec3(1.0f);
    };

    class DirectionalLight : public Light {
    public:
        DirectionalLight(const std::shared_ptr<ShaderProgram>& aShader, const glm::vec3& aDirection);
        [[nodiscard]] const glm::vec3& getDirection() const;
        void setDirection(const glm::vec3& aDirection);

        void setAmbient(const glm::vec3& aAmbientColor) override;
        void setDiffuse(const glm::vec3& aDiffuseColor) override;
        void setSpecular(const glm::vec3& aSpecularColor) override;

    private:
        glm::vec3 mDirection;
        inline static const std::string cDirectionUniformName{"dirLight.direction"};
        inline static const std::string cAmbientUniformName{"dirLight.ambient"};
        inline static const std::string cDiffuseUniformName{"dirLight.diffuse"};
        inline static const std::string cSpecularUniformName{"dirLight.specular"};
    };

    class PointLight : public Light {
    public:
        PointLight(const std::shared_ptr<ShaderProgram>& aShader, const glm::vec3& aPosition);
        [[nodiscard]] const glm::vec3& getPosition() const;
        void setPosition(const glm::vec3& aPosition);
        void setAmbient(const glm::vec3& aAmbientColor) override;
        void setDiffuse(const glm::vec3& aDiffuseColor) override;
        void setSpecular(const glm::vec3& aSpecularColor) override;

    protected:
        PointLight() = default;

    protected:
        glm::vec3 mPosition{};
        static constexpr float cConstant = 1.0f;
        static constexpr float cLinear = 0.045f;
        static constexpr float cQuadratic = 0.0075f;

    private:
        static uint8_t counter;
        std::string mIndex;
        // Later try to move to char arrays?

        std::string mPositionUniformName;
        std::string mAmbientUniformName;
        std::string mDiffuseUniformName;
        std::string mSpecularUniformName;
    };

    class Spotlight : public PointLight {
    public:
        Spotlight(const std::shared_ptr<ShaderProgram>& shader, const glm::vec3& aPosition, const glm::vec3& aDirection);
        [[nodiscard]] const glm::vec3& getDirection() const;
        void setDirection(const glm::vec3& aDirection);
        void setAmbient(const glm::vec3& aAmbientColor) override;
        void setDiffuse(const glm::vec3& aDiffuseColor) override;
        void setSpecular(const glm::vec3& aSpecularColor) override;

    private:
        glm::vec3 mDirection{};
        static constexpr float cCutOff = glm::radians(12.5f);
        static constexpr float cOuterCutOff = glm::radians(17.5f);

        inline static const std::string cDirectionUniformName{"spotLight.direction"};
        inline static const std::string cPositionUniformName{"spotLight.position"};

        inline static const std::string cAmbientUniformName{"spotLight.ambient"};
        inline static const std::string cDiffuseUniformName{"spotLight.diffuse"};
        inline static const std::string cSpecularUniformName{"spotLight.specular"};
    };
}// namespace Ouroboros
#endif//ENTRYPOINT_LIGHT_H
