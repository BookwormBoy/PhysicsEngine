#include "texture.h"
#include "stb_image.h"
#include "renderer.h"
#include <iostream>

Texture::Texture(const std::string& texturePath, const std::string& imageType, const std::string& name){

    this->name = name;
    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    stbi_set_flip_vertically_on_load(true); 


    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

    if(data){
        if(imageType=="jpg"){
            GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
        }
        else if(imageType=="png"){
            GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
        }
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void Texture::bind(unsigned int textureNumber){
    GLCall(glActiveTexture(GL_TEXTURE0 + textureNumber));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}
