#pragma once
#include "renderer.h"

class Texture{
    private:
        unsigned int m_RendererID;

    public:
        Texture(const std::string& texturePath, const std::string& imageType);
        void bind(unsigned int textureNumber);
        
};