#pragma once
#include "vertexArray.h"
#include "indexBuffer.h"
#include "shader.h"
#include "texture.h"
#include <vector>
#include <iostream>

class Shape{
    protected:
        VertexArray va;
        VertexBuffer vb;
        IndexBuffer ib;
        std::vector<Texture> textures;
        glm::vec3 position;
        float angle;
        glm::vec3 axis;
    public:
        Shape(const void* vertices, unsigned int vbSize,
          const unsigned* indices, unsigned int ibCount,
          glm::vec3 pos, float angle, glm::vec3 axis)
        : vb(vertices, vbSize), ib(indices, ibCount), position(pos), angle(angle), axis(axis){}
        void addTexture(Texture texture);
        void bindTextures(Shader& shader);
        virtual void draw() = 0;
        glm::mat4 getModelMatrix();
};

class Cube : public Shape{    
    public:
        Cube(glm::vec3 position, glm::vec3 axis, float angle);
        void draw() override;
};