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
#include "cloth.h"
#include "pcontact.h"
#include "plinks.h"

#include "ballistic.h"

#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window, Cloth& cloth);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

std::vector<struct Ballistic*> ballistics;
float last_shot = 0;

Camera camera(glm::vec3(0.0f, 0.0f, 30.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
// Cloth cloth(5, 5, 2, 10000, 0);


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

    Shader shader("../resources/shaders/cloth.shader");
    Cloth cloth(15, 15, 1, 10000, 20);
    

    // Texture woodTexture("../resources/textures/wood.jpg", "jpg", "texture1");
    // Texture awesomeFace("../resources/textures/awesomeface.png", "png", "texture2");
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {   

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, cloth);
        /* Render here */
        renderer.clear();

        renderer.setViewMatrix(camera.getViewMatrix());
        renderer.setProjectionMatrix(glm::perspective(glm::radians(camera.fov), 800.0f / 600.0f, 0.1f, 100.0f));

        cloth.update(deltaTime);
        renderer.drawCloth(cloth, shader);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    }
   
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window, Cloth& cloth){
    
    float currentFrame = static_cast<float>(glfwGetTime());

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if((glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) && (currentFrame-cloth.cut>1)){
        cloth.cut=static_cast<float>(glfwGetTime());
        cloth.cutString();
    }
    // if((glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) && (currentFrame-last_shot>1)){ 
    //     Ballistic* pistol = new Ballistic(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.3f, 0.5f), 40.0f);
    //     pistol->particle.setMass(2.0f); // 2.0kg
    //     pistol->particle.setVelocity(Vector3(0.0f, 0.0f, -500.0f)); // 35m/s
    //     pistol->particle.setAcceleration(Vector3(0.0f, -1.0f, 0.0f));
    //     pistol->particle.setDamping(0.99f);
    //     pistol->cube.addTexture(texture1);
    //     pistol->cube.addTexture(texture2);
    //     last_shot = static_cast<float>(glfwGetTime());
    //     ballistics.push_back(pistol);

    // }

    // if((glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) && (currentFrame-last_shot>1)){ 
    //     Ballistic* artillery = new Ballistic(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.3f, 0.5f), 40.0f);
    //     artillery->particle.setMass(200.0f); // 200.0kg
    //     artillery->particle.setVelocity(Vector3(0.0f, 0.0f, -50.0f)); // 50m/s
    //     artillery->particle.setAcceleration(Vector3(0.0f, -20.0f, 0.0f));
    //     artillery->particle.setDamping(0.99f);
    //     artillery->cube.addTexture(texture1);
    //     artillery->cube.addTexture(texture2);
    //     last_shot = static_cast<float>(glfwGetTime());
    //     ballistics.push_back(artillery);   
    // }

    // if((glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) && (currentFrame-last_shot>1)){ 
    //     Ballistic* fireball = new Ballistic(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.3f, 0.5f), 40.0f);
    //     fireball->particle.setMass(1.0f); // 1.0kg
    //     fireball->particle.setVelocity(Vector3(0.0f, 0.0f, -5.0f)); // 5m/s
    //     fireball->particle.setAcceleration(Vector3(0.0f, 0.6f, 0.0f));
    //     fireball->particle.setDamping(0.99f);
    //     fireball->cube.addTexture(texture1);
    //     fireball->cube.addTexture(texture2);
    //     last_shot = static_cast<float>(glfwGetTime());   
    //     ballistics.push_back(fireball);
    // }

    // if((glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) && (currentFrame-last_shot>1)){ 
    //     Ballistic* laser = new Ballistic(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.3f, 0.5f), 40.0f);
    //     laser->particle.setMass(0.1f); // 0.1kg
    //     laser->particle.setVelocity(Vector3(0.0f, 0.0f, -100.0f)); // 100m/s
    //     laser->particle.setAcceleration(Vector3(0.0f, 0.0f, 0.0f)); // no gravity
    //     laser->particle.setDamping(0.99f);
    //     laser->cube.addTexture(texture1);
    //     laser->cube.addTexture(texture2);
    //     last_shot = static_cast<float>(glfwGetTime());  
    //     ballistics.push_back(laser);
    // }

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