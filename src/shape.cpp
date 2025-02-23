#include "shape.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

void Shape::addTexture(Texture texture){
    textures.push_back(texture);
}

void Shape::bindTextures(Shader& shader){
    for(unsigned int i=0;i<textures.size();i++){
        textures[i].bind(i);
        shader.setUniform1i(textures[i].getName(), i);
    }
}

glm::mat4 Shape::getModelMatrix(){
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), axis);
    return model;
}

void Shape::setPosition(Vector3 v){
    position = glm::vec3(v.x, v.y, v.z);
}

