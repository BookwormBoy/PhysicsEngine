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

void Renderer::draw(Shape& shape, Shader& shader) const{
    shader.bind();
    shape.bindTextures(shader);
    shader.setUniformMatrix4fv("view", viewMatrix);
    shader.setUniformMatrix4fv("projection", projectionMatrix);
    shader.setUniformMatrix4fv("model", shape.getModelMatrix());
    shape.draw();
}

void Renderer::drawCloth(Cloth& cloth, Shader& shader) const{
    shader.bind();
    shader.setUniformMatrix4fv("view", viewMatrix);
    shader.setUniformMatrix4fv("projection", projectionMatrix);
    shader.setUniformMatrix4fv("model", glm::mat4(1.0f));
    shader.setUniform4f("colour", 1.0f, 1.0f, 1.0f, 1.0f);
    cloth.render();
}

void Renderer::clear() const{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::setViewMatrix(glm::mat4 view){
    viewMatrix = view;
}

void Renderer::setProjectionMatrix(glm::mat4 projection){
    projectionMatrix = projection;
}