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
/* TODO
 *  Texture refactoring
 *  Mesh to load interesting models
 *  Scene graph node data type
 *  General nodes
 *  Mesh nodes
 *  Light nodes
 *  Scene graph - creating, adding, traversing
 *  Material system - simple materials that encapsulate shading model, textures and other related properties
 *  GUI for editing object properties in real time
 *  Fixing warnings
 * */

auto camera = std::make_shared<Ouroboros::Camera>(glm::vec3(0.0f, 1.0f, 15.0f),
                                                               glm::vec3(0.0f, 0.0f, -1.0f),
                                                               glm::vec3(0.0f, 1.0f, 0.0f));
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

    auto shader = std::make_shared<Ouroboros::ShaderProgram>(
            Shader(R"(..\resources\shaders\vertex.shader)", GL_VERTEX_SHADER),
            Shader(R"(..\resources\shaders\fragment.shader)", GL_FRAGMENT_SHADER));


    auto boxTextureDiffuse = std::make_shared<Ouroboros::Diffuse>(R"(..\resources\textures\tiles.png)");
    auto boxTextureSpecular = std::make_shared<Ouroboros::Specular>(R"(..\resources\textures\tiles.png)");

    auto planeTextureDiffuse = std::make_shared<Ouroboros::Diffuse>(R"(..\resources\textures\wall.png)");
    auto planeTextureSpecular = std::make_shared<Ouroboros::Specular>(R"(..\resources\textures\wall.png)");

    shader->use();

    auto spotlight = Ouroboros::Spotlight(shader, camera->position(), camera->direction());

    auto scene = Ouroboros::Scene();


    auto processInput = [&spotlight](GLFWwindow *window, float deltaTime) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera->keyboardInput(Ouroboros::Camera::CameraMovement::Forward, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera->keyboardInput(Ouroboros::Camera::CameraMovement::Backward, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera->keyboardInput(Ouroboros::Camera::CameraMovement::Left, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera->keyboardInput(Ouroboros::Camera::CameraMovement::Right, deltaTime);
        }
    };

    float deltaTime;
    float lastFrame{};
    while (!glfwWindowShouldClose(window)) {
        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, deltaTime);
        spotlight.setPosition(camera->position());
        spotlight.setDirection(camera->direction());

        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.render();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}