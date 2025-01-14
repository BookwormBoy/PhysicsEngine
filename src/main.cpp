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
#include "texture.h"
#include "camera.h"

#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()){
        std::cout<<"glfw failed"<<std::endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
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
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};

    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));

    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    va.addBuffer(vb, layout);
    vb.unbind();

    IndexBuffer ib(indices, sizeof(indices));
    va.addIndexBuffer(ib);
    va.unbind();
    ib.unbind();

    GLCall(glEnable(GL_DEPTH_TEST));

    Shader shader("../resources/shaders/basic.shader");

    Texture woodTexture("../resources/textures/wood.jpg", "jpg");
    Texture awesomeFace("../resources/textures/awesomeface.png", "png");

    shader.bind();
    shader.setUniform1i("woodTexture", 0);
    shader.setUniform1i("awesomeFace", 1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {   

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        /* Render here */
        renderer.clear();

        woodTexture.bind(0);
        awesomeFace.bind(1);

        glm::mat4 view;
        view = camera.getViewMatrix();

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        shader.setUniformMatrix4fv("view", view);
        shader.setUniformMatrix4fv("projection", projection);

        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setUniformMatrix4fv("model", model);

            renderer.draw(va, shader);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    }
   
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    camera.processKeyboard(window, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera.processMouseScroll(window, xoffset, yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}