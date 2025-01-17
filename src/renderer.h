#pragma once
#include <glad/glad.h>
#include <csignal>

#include "vertexArray.h"
#include "indexBuffer.h"
#include "shader.h"

#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer{
    public:
        void draw(const VertexArray& va, const Shader& shader) const;
        void clear() const;


};