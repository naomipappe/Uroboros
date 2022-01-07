#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <fstream>
#include <sstream>

#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader {
public:
    Shader(const std::string& shaderSourcePath, GLenum shaderType);
    Shader(const Shader&) = delete;
    Shader(Shader&& from) noexcept;
    [[nodiscard]] uint32_t getID() const;
    ~Shader();

private:
    static std::string loadFromFile(const std::string& pathToFile);

private:
    uint32_t id;
    static const size_t infoLogSize = 512;
};
#endif