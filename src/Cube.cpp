#include <Cube.h>

uint32_t Cube::VBO{};
uint32_t Cube::VAO{};
uint32_t Cube::cubeInstancesAmount{};

Cube::Cube(std::shared_ptr<Camera> camera) : m_camera(std::move(camera)) {
    m_shader = std::make_shared<ShaderProgram>(
            Shader(R"(..\Shaders\vertex_default.shader)", GL_VERTEX_SHADER),
            Shader(R"(..\Shaders\fragment_default.shader)", GL_FRAGMENT_SHADER));
    m_texture = nullptr;
}

Cube::Cube(std::shared_ptr<Camera> camera,
           std::shared_ptr<ShaderProgram> shader,
           std::shared_ptr<Texture> texture) {
    initialize();
    m_camera = std::move(camera);
    m_shader = std::move(shader);
    m_texture = std::move(texture);
    m_shader->setDiffuseMap(m_texture);
    m_shader->setSpecularMap(m_texture);
    m_shader->setShininess(m_texture);

    ++cubeInstancesAmount;
}
void Cube::setPosition(const glm::vec3 &position) {
    m_position = position;
}

void Cube::setRotation(float angle, const glm::vec3 &rotationAxis) {
    m_rotation = glm::angleAxis(glm::radians(angle), rotationAxis);
}

void Cube::setScale(const glm::vec3 &scale) {
    m_scale = scale;
}

glm::vec3 Cube::position() const {
    return m_position;
}

std::pair<float, glm::vec3> Cube::rotation() const {
    return std::make_pair(glm::angle(m_rotation), glm::axis(m_rotation));
}


void Cube::update() {
    glBindVertexArray(VAO);

    m_shader->use();
    if (m_texture) {
        m_texture->bind();
    }

    auto model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);
    model = glm::rotate(model, glm::angle(m_rotation), glm::axis(m_rotation));
    model = glm::scale(model, m_scale);

    auto normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));

    m_shader->setUniform("model", model);
    m_shader->setUniform("view", m_camera->view());
    m_shader->setUniform("projection", m_camera->projection());
    m_shader->setUniform("normalMatrix", normalMatrix);
    m_shader->setUniform("viewerPosition", m_camera->position());

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

Cube::~Cube() {
    if (cubeInstancesAmount > 0) {
        --cubeInstancesAmount;
    } else if (cubeInstancesAmount == 0) {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
}

void Cube::initialize() {
    if (VAO) {
        return;
    }
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}


Plane::Plane(std::shared_ptr<Camera> camera, std::shared_ptr<ShaderProgram> shader, std::shared_ptr<Texture> texture)
    : Cube(std::move(camera),
           std::move(shader),
           std::move(texture)) {
    m_scale = glm::vec3(m_scale.x, m_scale.y * 0.1, m_scale.z);
}

Box::Box(std::shared_ptr<Camera> camera) : Cube(std::move(camera)) {
}
Box::Box(std::shared_ptr<Camera> camera, std::shared_ptr<ShaderProgram> shader, std::shared_ptr<Texture> texture)
    : Cube(std::move(camera),
           std::move(shader),
           std::move(texture)) {
}
