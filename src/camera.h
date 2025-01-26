#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Camera{

    private:
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        bool firstMouse = true;
        float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
        float pitch =  0.0f;
        float lastX = 400;
        float lastY = 300;

    public:
        float fov   =  45.0f;
        Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);
        void processKeyboard(GLFWwindow* window, float deltaTime);
        void processMouseMovement(double xposIn, double yposIn);
        void processMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
        glm::mat4 getViewMatrix();
};