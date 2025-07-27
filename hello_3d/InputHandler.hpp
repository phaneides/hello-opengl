
#pragma once
#include <GLFW/glfw3.h>
#include "Camera.hpp"

class InputHandler {
public:
    static void initialize(GLFWwindow* window, Camera* cam);

    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
    static inline float lastX = 400.0f;
    static inline float lastY = 300.0f;
    static inline bool firstMouse = true;

    static inline Camera* camera = nullptr;
};
