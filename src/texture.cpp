#include <texture.h>

namespace Ouroboros {

    Texture::Texture(const std::string& aSourcePath, const uint8_t& aTextureUnit) : mTextureUnit(aTextureUnit) {
        mFilename = aSourcePath.substr(aSourcePath.find_last_of('\\')+1);
        mID = loadFromFile(aSourcePath);
    }

    Texture::Texture(Texture&& aOther) noexcept {
        mID = std::exchange(aOther.mID, 0);
    }

    Texture& Texture::operator=(Texture&& aOther) noexcept {
        if (this != &aOther) {
            unbind();
            glDeleteTextures(1, &(mID));
            mID = std::exchange(aOther.mID, 0);
        }
        return *this;
    }

    void Texture::bind() const {
        glActiveTexture(GL_TEXTURE0 + mTextureUnit);
        glBindTexture(Target, mID);
    }

    void Texture::unbind() const {
        glActiveTexture(GL_TEXTURE0 + mTextureUnit);
        glBindTexture(Target, mID);
    }

    const std::string Texture::path() const {
        return mFilename;
    }

    Texture::~Texture() {
        glDeleteTextures(1, &(mID));
    }

    uint32_t Texture::loadFromFile(const std::string& aSourcePath) {
        uint32_t id{};
        glGenTextures(1, &id);

        int width, height, nrComponents;
        unsigned char* data = stbi_load(
                aSourcePath.c_str(), &width, &height, &nrComponents, 0);
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
        }

        stbi_image_free(data);

        return id;
    }

    Diffuse::Diffuse(const std::string& aSourcePath) : Texture(aSourcePath, cTextureUnitDiffuse) {
    }

    Specular::Specular(const std::string& aSourcePath, float aShininess) : Texture(aSourcePath, cTextureUnitSpecular) {
        mShininess = aShininess;
    }

}// namespace Ouroboros