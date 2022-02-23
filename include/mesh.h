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
    
    static constexpr auto VertexSize = sizeof(Vertex);
    static constexpr auto IndexSize = sizeof(uint32_t);
    
    // TODO Generalize this to arbitrary geometry
    // Geometry can be represented as a triangular mesh, but it is not an only option
    class Mesh {
    public:
        Mesh(std::vector<Vertex> &, std::vector<uint32_t> &, std::vector<std::shared_ptr<Texture>> &);
        Mesh(std::vector<Vertex> &&, std::vector<uint32_t> &&, std::vector<std::shared_ptr<Texture>> &&);


        // TODO Extract this to a renderer type
        // Renderer should know how to render geometry, but geometry should not have any knowledge about underlying rendering api
        void draw(ShaderProgram &);

    private:
        uint32_t VBO{}, EBO{}, VAO{};
        // Consider here some ways to reduce the data overhead for multiple objects
        // E.G. for instanced drawing we really need only one set of this data to draw the object
        std::vector<Vertex> mVertices;
        std::vector<uint32_t> mIndices;
        std::vector<std::shared_ptr<Texture>> mTextures;

    private:
        void setup();
    };

}// namespace Ouroboros

#endif//ENTRYPOINT_MESH_H
