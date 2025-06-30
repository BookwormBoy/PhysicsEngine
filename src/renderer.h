#pragma once
#include <glad/glad.h>
#include <csignal>

// #include "vertexArray.h"
// #include "indexBuffer.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shape.h"
#include "cloth.h"

#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer{
    private:
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
    public:
        void draw(Shape& shape, Shader& shader) const;
        void drawCloth(Cloth& cloth, Shader& shader) const;
        void clear() const;
        void setViewMatrix(glm::mat4 view);
        void setProjectionMatrix(glm::mat4 projection);

};