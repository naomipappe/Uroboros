#ifndef ENTRYPOINT_TEXTURE_H
#define ENTRYPOINT_TEXTURE_H
#include <memory>
#include <string>

#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

class Texture {
public:
    Texture(const std::string& diffuseSourcePath, const std::string& specularSourcePath, float shininess);

    void bind() const;
    void unbind() const;

    ~Texture();

private:
    struct ID {
        uint32_t m_diffuseID;
        uint32_t m_specularID;
    } textureID;
    float materialShininess;
    friend class ShaderProgram;
    GLenum Target = GL_TEXTURE_2D;
    GLenum Type = GL_UNSIGNED_BYTE;
    GLenum FilterMin = GL_LINEAR_MIPMAP_LINEAR;
    GLenum FilterMag = GL_LINEAR;
    GLenum WrapS = GL_REPEAT;
    GLenum WrapT = GL_REPEAT;

private:
    [[nodiscard]] uint32_t loadFromFile(const std::string& path) const;
};

#endif//ENTRYPOINT_TEXTURE_H
