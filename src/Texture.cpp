#include <Texture.h>

Texture::Texture(const std::string& diffuseSourcePath, const std::string& specularSourcePath, float shininess) : textureID() {
    textureID.m_diffuseID = loadFromFile(diffuseSourcePath);
    textureID.m_specularID = loadFromFile(specularSourcePath);
    materialShininess = shininess;
}
Texture::~Texture() {
    unbind();
    glDeleteTextures(1, &(textureID.m_diffuseID));
    glDeleteTextures(1, &(textureID.m_specularID));
}
void Texture::bind() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(Target, textureID.m_diffuseID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(Target, textureID.m_specularID);
}
void Texture::unbind() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(Target, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(Target, 0);
}

uint32_t Texture::loadFromFile(const std::string& path) const {
    uint32_t id{};
    glGenTextures(1, &id);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format{};
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(Target, id);
        glTexImage2D(Target, 0, format, width, height, 0, format, Type, data);
        glGenerateMipmap(Target);

        glTexParameteri(Target, GL_TEXTURE_WRAP_S, WrapS);
        glTexParameteri(Target, GL_TEXTURE_WRAP_T, WrapT);
        glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, FilterMin);
        glTexParameteri(Target, GL_TEXTURE_MAG_FILTER, FilterMag);

        stbi_image_free(data);
    } else {
        stbi_image_free(data);
    }
    return id;
}
