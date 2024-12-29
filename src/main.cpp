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

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()){
        std::cout<<"glfw failed"<<std::endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout<<"window creation failed"<<std::endl;
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

     // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return -1;
    }
   
    {
    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va;
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));

    VertexBufferLayout layout;
    layout.push<float>(2);
    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    Shader shader("../resources/shaders/basic.shader");
    shader.bind();
    shader.setUniform4f("u_Colour", 0.0f, 0.3f, 0.8f, 1.0f);

    va.unbind();
    shader.unbind();
    vb.unbind();
    ib.bind();
    
    float r = 0.0f;
    float increment = 0.05f;

    Renderer renderer;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.clear();

        shader.bind();
        shader.setUniform4f("u_Colour", r, 0.3f, 0.8f, 1.0f); 

        renderer.draw(va, ib, shader);

        if(r>1.0f){
            increment = -0.01f;
        }
        else if(r<0.0f){
            increment = 0.01f;
        }

        r+=increment;
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    }

    glfwTerminate();
    return 0;
}