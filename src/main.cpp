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
#include "shape.h"

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

glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);  
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
    

    GLCall(glEnable(GL_DEPTH_TEST));

    Shader shader("../resources/shaders/basic.shader");

    Texture woodTexture("../resources/textures/wood.jpg", "jpg", "texture1");
    Texture awesomeFace("../resources/textures/awesomeface.png", "png", "texture2");

    Cube cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.3f, 0.5f), 40.0f);
    cube.addTexture(woodTexture);
    cube.addTexture(awesomeFace);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {   

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        /* Render here */
        renderer.clear();


        renderer.setViewMatrix(camera.getViewMatrix());
        renderer.setProjectionMatrix(glm::perspective(glm::radians(camera.fov), 800.0f / 600.0f, 0.1f, 100.0f));
        renderer.draw(cube, shader);
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