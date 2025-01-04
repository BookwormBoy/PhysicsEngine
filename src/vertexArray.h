#pragma once
#include "vertexBuffer.h"
#include "indexBuffer.h"
class VertexBufferLayout;

class VertexArray{
    private: 
        unsigned int m_RendererID;
        unsigned int indexBufferElementsCount;
    public:
        VertexArray();
        ~VertexArray();

        void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
        void addIndexBuffer(const IndexBuffer& ib);
        void bind() const;
        void unbind() const;

        inline unsigned int getIndexBufferElementsCount() const {return indexBufferElementsCount;}
};