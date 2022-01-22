#include <shaderprogram.h>
namespace Ouroboros {
    const std::string ShaderProgram::diffuseUniformName = "material.diffuse_map";
    const std::string ShaderProgram::specularUniformName = "material.specular_map";

    ShaderProgram::ShaderProgram(Shader&& vertexShader, Shader&& fragmentShader) noexcept : id{} {
        createShaderProgram(vertexShader.getID(), fragmentShader.getID());
    }

    ShaderProgram::ShaderProgram(std::unique_ptr<Shader> vertexShader, std::unique_ptr<Shader> fragmentShader) : id{} {
        createShaderProgram(vertexShader->getID(), fragmentShader->getID());
    }

    void ShaderProgram::createShaderProgram(uint32_t vertexShaderId, uint32_t fragmentShaderId) {
        id = glCreateProgram();
        glAttachShader(id, vertexShaderId);
        glAttachShader(id, fragmentShaderId);
        glLinkProgram(id);
        int success;

        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[ShaderProgram::infoLogSize];
            glGetProgramInfoLog(id, ShaderProgram::infoLogSize, nullptr, infoLog);
            throw std::runtime_error(std::string("ERROR::SHADER::PROGRAM::LINK_FAILED\n").append(infoLog));
        }
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(id);
    }

    void ShaderProgram::use() const {
        glUseProgram(id);
    }

    void ShaderProgram::setUniform(const std::string& uniformName, const int& value) {
        glUniform1i(glGetUniformLocation(id, uniformName.c_str()), value);
    }

    void ShaderProgram::setUniform(const std::string& uniformName, const bool& value) {
    glUniform1i(glGetUniformLocation(id, uniformName.c_str()), value);
}

void ShaderProgram::setUniform(const std::string& uniformName, const float& value) {
    glUniform1f(glGetUniformLocation(id, uniformName.c_str()), value);
}
void ShaderProgram::setUniform(const std::string& uniformName, const glm::mat4& value) {
    glUniformMatrix4fv(glGetUniformLocation(id, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void ShaderProgram::setUniform(const std::string& uniformName, const glm::vec3& value) {
    glUniform3fv(glGetUniformLocation(id, uniformName.c_str()), 1, glm::value_ptr(value));
}
void ShaderProgram::setUniform(const std::string& uniformName, const glm::mat3& value) {
    glad_glUniformMatrix3fv(glGetUniformLocation(id, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

}// namespace Ouroboros