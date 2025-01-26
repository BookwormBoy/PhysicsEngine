#pragma once
#include <string>
class Texture{
    private:
        unsigned int m_RendererID;
        std::string name;
    public:
        Texture(const std::string& texturePath, const std::string& imageType, const std::string& name);
        void bind(unsigned int textureNumber);
        inline std::string getName(){return name;}
};