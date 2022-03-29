#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <fstream>
#include <sstream>

#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Uroboros {
    class Shader {
    public:
        enum class Type {
            Vertex,
            Fragment
        };
        Shader(const std::string& aSourcePath, Type aType);
        Shader(const Shader&) = delete;
        Shader(Shader&&) noexcept;
        [[nodiscard]] uint32_t getID() const;
        ~Shader();

    private:
        static std::string loadFromFile(const std::string& aSourcePath);

    private:
        uint32_t id;
        static constexpr size_t infoLogSize = 512;
    };
}// namespace Uroboros
#endif