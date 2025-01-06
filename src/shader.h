#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

// #pragma once

struct ShaderProgramSource{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader{
    private:
        unsigned int m_RendererID;
        std::string m_FilePath;
        std::unordered_map<std::string, int> m_UniformLocationCache;
    public:
        Shader(const std::string& filepath);
        ~Shader();
        void bind() const;
        void unbind() const;

        void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void setUniform1f(const std::string &name, float f);
        void setUniform1i(const std::string &name, int i);
        void setUniformMatrix4fv(const std::string &name, glm::mat4 matrix);

        unsigned int getUniformLocation(const std::string& name);

        unsigned int compileShader(unsigned int type, const std::string& source);
        unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
        ShaderProgramSource parseShader(const std::string& filepath);
};