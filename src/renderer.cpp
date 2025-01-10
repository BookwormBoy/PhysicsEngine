#include "renderer.h"
#include <GLFW/glfw3.h>
#include <iostream>

void GLClearError(){
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line){
    while(GLenum error = glGetError()){
        std::cout<<"[OpenGL Error] ("<<error<<")"<<function<<" "<<file<<":"<<line<<std::endl;
        return false;
    }
    return true;
}

void Renderer::draw(const VertexArray& va, const Shader& shader) const{
    shader.bind();
    va.bind();

    GLCall(glDrawElements(GL_TRIANGLES, va.getIndexBufferElementsCount(), GL_UNSIGNED_INT, nullptr));

}

void Renderer::clear() const{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
