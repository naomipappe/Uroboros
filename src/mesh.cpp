#include <mesh.h>


namespace Uroboros {
    Mesh::Mesh(std::vector<Vertex> &aVertices, std::vector<uint32_t> &aIndices, std::vector<std::shared_ptr<Texture>> &aTextures) {
        mVertices = aVertices;
        mIndices = aIndices;
        mTextures = aTextures;
        setup();
    }

    Mesh::Mesh(std::vector<Vertex> &&aVertices, std::vector<uint32_t> &&aIndices, std::vector<std::shared_ptr<Texture>> &&aTextures) {
        mVertices = std::move(aVertices);
        mIndices = std::move(aIndices);
        mTextures = std::move(aTextures);
        setup();
    }

    void Mesh::setup() {
        // Generate the vertex array and buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Bind buffers and send data
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, mVertices.size() * VertexSize, mVertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * IndexSize, mIndices.data(), GL_STATIC_DRAW);

        // Vertex Attribute Array Configuration
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexSize, (void *) 0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VertexSize, (void *) offsetof(Vertex, mNormal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VertexSize, (void *) offsetof(Vertex, mTextureCoordinates));

        glBindVertexArray(0);
    }

    void Mesh::draw(ShaderProgram &aProgram) {
        //For now, we consider that there is exactly one diffuse, specular and normal map per mesh
        for (const auto& texture : mTextures) {
            texture->bind();
        }

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
    }
}// namespace Ouroboros