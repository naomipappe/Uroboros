#include <shader.h>


Shader::Shader(const std::string& shaderSourcePath, GLenum shaderType) : id{} {
    std::string shaderSource = loadFromFile(shaderSourcePath);
    int success;
    auto shaderSourceRaw = shaderSource.c_str();

    id = glCreateShader(shaderType);
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

std::string Shader::loadFromFile(const std::string& pathToFile)
{
	std::ifstream shaderFile;
    std::string shaderSource{};
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(pathToFile);
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