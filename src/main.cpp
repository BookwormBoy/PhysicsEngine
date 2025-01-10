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
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

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

    const float radius = 20.0f;


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {   

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        /* Render here */
        renderer.clear();

        // shader.setUniform1f("offset", offset);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, woodTexture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, awesomeFace);

        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);  

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


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    }


   
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
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

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}