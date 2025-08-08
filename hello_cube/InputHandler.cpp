
#include "InputHandler.hpp"

void InputHandler::initialize(GLFWwindow* window, Camera* cam) {
    camera = cam;
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void InputHandler::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed

    lastX = xpos;
    lastY = ypos;

    if (camera) {
        camera->processMouseMovement(xoffset, yoffset);
    }
}

void InputHandler::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    if (camera) {
        camera->processScroll((float)yoffset);
    }
}
