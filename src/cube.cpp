#include "shape.h"
#include "vertexBufferLayout.h"
#include "shapeData.h"
#include <iostream>


Cube::Cube(glm::vec3 position, glm::vec3 axis, float angle) : Shape(cubeVertices, sizeof(cubeVertices), cubeIndices, sizeof(cubeIndices)/sizeof(unsigned int), position, angle, axis){
    
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    va.addBuffer(vb, layout);
    vb.unbind();

    va.addIndexBuffer(ib);
    va.unbind();
    ib.unbind();
};

void Cube::draw(){
    va.bind();
    GLCall(glDrawElements(GL_TRIANGLES, va.getIndexBufferElementsCount(), GL_UNSIGNED_INT, nullptr));
}
