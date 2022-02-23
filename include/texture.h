#ifndef ENTRYPOINT_TEXTURE_H
#define ENTRYPOINT_TEXTURE_H
#include <memory>
#include <string>

#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

//TODO multiple textures using
// Each object has at least several textures - diffuse map, specular map, normal map, etc.
// We can configure texture units to correspond to this types of textures
// For instance, texture unit 0 GL_TEXTURE0 is always a diffuse map, and so on

namespace Ouroboros {

    class Texture {
    public:
        Texture(const Texture&) = delete;
        Texture(Texture&&) noexcept;

        Texture& operator=(const Texture&) = delete;
        Texture& operator=(Texture&&) noexcept;

        void bind() const;
        void unbind() const;
        
        const std::string path() const;
        
        virtual ~Texture();

    protected:
        uint32_t mID{};
        // This is rather dirty hack. Try to enforce the texture unit at compile time somehow
        const uint8_t mTextureUnit = 0;
        static constexpr GLenum Target = GL_TEXTURE_2D;
        static constexpr GLenum Type = GL_UNSIGNED_BYTE;
        static constexpr GLenum FilterMin = GL_LINEAR_MIPMAP_LINEAR;
        static constexpr GLenum FilterMag = GL_LINEAR;
        static constexpr GLenum WrapS = GL_REPEAT;
        static constexpr GLenum WrapT = GL_REPEAT;
        std::string mFilename;

    protected:
        Texture(const std::string& aSourcePath, const uint8_t&);
        [[nodiscard]] static uint32_t loadFromFile(const std::string& aSourcePath);
    };

    class Diffuse : public Texture {
    public:
        explicit Diffuse(const std::string& aSourcePath);
        // explicit Diffuse(const std::string_view& aSourcePath);
        ~Diffuse() override = default;

    public:
        static constexpr uint8_t cTextureUnitDiffuse = 0;
    };

    class Specular : public Texture {
    public:
        explicit Specular(const std::string& aSourcePath, float aShininess = 32.0f);
        // explicit Specular(const std::string_view& aSourcePath, float aShininess = 32.0f);

        ~Specular() override = default;

    public:
        static constexpr uint8_t cTextureUnitSpecular = 1;

    private:
        float mShininess;
    };

    class Normal : public Texture {
    public:
        static constexpr uint8_t cTextureUnitNormal = 2;
    };

}// namespace Ouroboros

#endif//ENTRYPOINT_TEXTURE_H
