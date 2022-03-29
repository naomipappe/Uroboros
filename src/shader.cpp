#include <shader.h>

namespace Uroboros {
    Shader::Shader(const std::string& aSourcePath, Type aType) : id{} {
        std::string shaderSource = loadFromFile(aSourcePath);
        int success;
        auto shaderSourceRaw = shaderSource.c_str();
        switch (aType) {

            case Type::Vertex:
                id = glCreateShader(GL_VERTEX_SHADER);
                break;
            case Type::Fragment:
                id = glCreateShader(GL_FRAGMENT_SHADER);
                break;
        }
        glShaderSource(id, 1, &shaderSourceRaw, nullptr);
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[Shader::infoLogSize];
        glGetShaderInfoLog(id, Shader::infoLogSize, nullptr, infoLog);
        auto errorMsg = std::string("ERROR::SHADER::COMPILATION_FAILED\n").append(std::string(infoLog));
        throw std::runtime_error(errorMsg);
    }
}

Shader::Shader(Shader&& from) noexcept : id(std::exchange(from.id, 0)) {
}

Shader::~Shader() {
	glDeleteShader(id);
}

std::string Shader::loadFromFile(const std::string& aSourcePath) {
    std::ifstream shaderFile;
    std::string shaderSource{};
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(aSourcePath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderSource = shaderStream.str();
    } catch (const std::ifstream::failure& e) {
        throw e;
    }
    return shaderSource;
}

uint32_t Shader::getID() const {
	return id;
}
}// namespace Uroboros