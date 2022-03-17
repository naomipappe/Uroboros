#define GLFW_DLL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>


#include <iostream>
#include <set>

#include <shader.h>
#include <shaderprogram.h>
#include <camera.h>
#include <scene.h>
#include <light.h>
#include <model.h>

/* TODO
 *  Texture refactoring
 *  Mesh to load interesting models
 *  fmt library for io
 *  remove exceptions for checked result akin to rust result or std::expected
 *  Scene graph node data type
 *  General nodes
 *  Mesh nodes
 *  Light nodes
 *  Scene graph - creating, adding, traversing
 *  Material system - simple materials that encapsulate shading model, textures and other related properties
 *  GUI for editing object properties in real time
 *  Fixing warnings
 * */

auto camera = std::make_shared<Uroboros::Camera>();
bool firstMouse = true;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;

void framebuffer_callback(GLFWwindow *window, int width, int height) {
    camera->setAspectRatio(static_cast<float>(width), static_cast<float>(height));
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    camera->mouseInput(xoffset, yoffset);
}

int main() {
    static const size_t width = 800, height = 600;

    stbi_set_flip_vertically_on_load(true);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the GLFW window and store it in GLFW window pointer
    auto window = glfwCreateWindow(width, height, "EntryPoint", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("GLFW window creation failed");
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("GLAD failed to initialize");
    }

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);


    camera->setAspectRatio(width, height);

    auto shader = std::make_shared<Uroboros::ShaderProgram>(
            Uroboros::Shader(R"(..\resources\shaders\vertex.shader)", Uroboros::Shader::Type::Vertex),
            Uroboros::Shader(R"(..\resources\shaders\fragment_phong.shader)", Uroboros::Shader::Type::Fragment));

    shader->use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    shader->setUniform("model", model);

    glm::mat4 normal(model);
    normal = glm::transpose(glm::inverse(normal));
    shader->setUniform("normalMatrix", glm::mat3(normal));

    Uroboros::Model backpack(R"(..\resources\models\backpack\backpack.obj)");

    shader->setUniform("material.shininess", 32.0f);
    shader->setUniform("PointLightsCount", 0);

    auto dir = Uroboros::DirectionalLight(shader, glm::vec3(0, -1, 0));
    auto torch = Uroboros::Spotlight(shader, camera->position(), camera->direction());

    auto processInput = [](GLFWwindow *window, float deltaTime) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera->keyboardInput(Uroboros::Camera::CameraMovement::Forward, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera->keyboardInput(Uroboros::Camera::CameraMovement::Backward, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera->keyboardInput(Uroboros::Camera::CameraMovement::Left, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera->keyboardInput(Uroboros::Camera::CameraMovement::Right, deltaTime);
        }
    };

    float deltaTime;
    float lastFrame{};
    while (!glfwWindowShouldClose(window)) {
        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, deltaTime);

        shader->setUniform("projection", camera->projection());
        shader->setUniform("view", camera->view());
        shader->setUniform("viewPos", camera->position());

        torch.setPosition(camera->position());
        torch.setDirection(camera->direction());


        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        backpack.draw(*shader);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}