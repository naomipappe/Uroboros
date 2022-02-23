#ifndef ENTRYPOINT_MESH_H
#define ENTRYPOINT_MESH_H

#include <glm/glm.hpp>

#include <vector>

#include <texture.h>
#include <shaderprogram.h>

namespace Ouroboros {
    struct Vertex {
        glm::vec3 mPosition;
        glm::vec3 mNormal;
        glm::vec2 mTextureCoordinates;
    };

    class Mesh {
    public:
        Mesh(std::vector<Vertex> &&, std::vector<uint32_t> &&, std::vector<Texture> &&);

        void draw(ShaderProgram &);

    private:
        uint32_t VBO, EBO, VAO;

    private:
        void setup();
    };

}// namespace Ouroboros

#endif//ENTRYPOINT_MESH_H
