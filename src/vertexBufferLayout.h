#pragma once
#include <vector>
#include <glad/glad.h>
#include "renderer.h"
struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    VertexBufferElement(unsigned int t, unsigned int c, unsigned char n)
        : type(t), count(c), normalized(n) {}

    static unsigned int getSizeOfType(unsigned int type){
        switch (type){
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    };
};

class VertexBufferLayout{
    private:
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride;
    public:
        VertexBufferLayout() : m_Stride(0) {};

        template<typename t>
        void push(unsigned int count);
        

        inline const std::vector<VertexBufferElement> getElements() const {return m_Elements;}
        inline unsigned int getStride() const {return m_Stride;}
};

template<>
void VertexBufferLayout::push<float>(unsigned int count);

template<>
void VertexBufferLayout::push<unsigned int>(unsigned int count);

template<>
void VertexBufferLayout::push<unsigned char>(unsigned int count);
