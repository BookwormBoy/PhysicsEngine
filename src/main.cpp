#include "renderer.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "shader.h"
#include "vertexBufferLayout.h"

#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()){
        std::cout<<"glfw failed"<<std::endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout<<"window creation failed"<<std::endl;
        glfwTerminate();
        return -1;
    }

    Renderer renderer;

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSwapInterval(1);

     // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return -1;
    }
   
    {
    
    
    float vertices[] = {
        //positions            //texture coords

        //front face
        -0.5f, -0.5f,  0.5f,     0.0f, 0.0f, //bottom left
        -0.5f,  0.5f,  0.5f,     0.0f, 1.0f, //top left
         0.5f,  0.5f,  0.5f,     1.0f, 1.0f, //top right
         0.5f, -0.5f,  0.5f,     1.0f, 0.0f, //bottom right

         //left face
        -0.5f, -0.5f, -0.5f,     0.0f, 0.0f, //bottom left
        -0.5f,  0.5f, -0.5f,     0.0f, 1.0f, //top left
        -0.5f,  0.5f,  0.5f,     1.0f, 1.0f, //top right
        -0.5f, -0.5f,  0.5f,     1.0f, 0.0f, //bottom right

         //right face
         0.5f, -0.5f,  0.5f,     0.0f, 0.0f, //bottom left
         0.5f,  0.5f,  0.5f,     0.0f, 1.0f, //top left
         0.5f,  0.5f, -0.5f,     1.0f, 1.0f, //top right
         0.5f, -0.5f, -0.5f,     1.0f, 0.0f, //bottom right

         //top face
        -0.5f,  0.5f,  0.5f,     0.0f, 0.0f, //bottom left
        -0.5f,  0.5f, -0.5f,     0.0f, 1.0f, //top left
         0.5f,  0.5f, -0.5f,     1.0f, 1.0f, //top right
         0.5f,  0.5f,  0.5f,     1.0f, 0.0f, //bottom right

         //bottom face
        -0.5f, -0.5f, -0.5f,     0.0f, 0.0f, //bottom left
        -0.5f, -0.5f,  0.5f,     0.0f, 1.0f, //top left
         0.5f, -0.5f,  0.5f,     1.0f, 1.0f, //top right
         0.5f, -0.5f, -0.5f,     1.0f, 0.0f, //bottom right

         //back face
         0.5f, -0.5f, -0.5f,     0.0f, 0.0f, //bottom left
         0.5f,  0.5f, -0.5f,     0.0f, 1.0f, //top left
        -0.5f,  0.5f, -0.5f,     1.0f, 1.0f, //top right
        -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, //bottom right
        

    };

    unsigned int stride = 4;

    unsigned int indices[] = {
        //front face
        (stride*0)+0, (stride*0)+1, (stride*0)+3,
        (stride*0)+1, (stride*0)+2, (stride*0)+3,

       //left face
        (stride*1)+0, (stride*1)+1, (stride*1)+3,
        (stride*1)+1, (stride*1)+2, (stride*1)+3,

        //right face
        (stride*2)+0, (stride*2)+1, (stride*2)+3,
        (stride*2)+1, (stride*2)+2, (stride*2)+3,

        //top face
        (stride*3)+0, (stride*3)+1, (stride*3)+3,
        (stride*3)+1, (stride*3)+2, (stride*3)+3,

        //bottom face
        (stride*4)+0, (stride*4)+1, (stride*4)+3,
        (stride*4)+1, (stride*4)+2, (stride*4)+3,

        //back face
        (stride*5)+0, (stride*5)+1, (stride*5)+3,
        (stride*5)+1, (stride*5)+2, (stride*5)+3,
    };


    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));

    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, sizeof(indices));
    va.addIndexBuffer(ib);
    va.unbind();

    glEnable(GL_DEPTH_TEST);

    Shader shader("../resources/shaders/basic.shader");
    // shader.bind();
    // shader.setUniform1f("offset", 0.0f);

    // shader.unbind();
    vb.unbind();
    // ib.bind();

    unsigned int woodTexture;
    glGenTextures(1, &woodTexture);
    glBindTexture(GL_TEXTURE_2D, woodTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true); 


    int width, height, nrChannels;
    unsigned char *data = stbi_load("../resources/textures/wood.jpg", &width, &height, &nrChannels, 0);

    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);



    unsigned int awesomeFace;
    glGenTextures(1, &awesomeFace);
    glBindTexture(GL_TEXTURE_2D, awesomeFace);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("../resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    shader.bind();
    shader.setUniform1i("woodTexture", 0);
    shader.setUniform1i("awesomeFace", 1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.clear();

        // shader.setUniform1f("offset", offset);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, woodTexture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, awesomeFace);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));  

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        shader.setUniformMatrix4fv("model", model);
        shader.setUniformMatrix4fv("view", view);
        shader.setUniformMatrix4fv("projection", projection);

        renderer.draw(va, ib, shader);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    }


   
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}