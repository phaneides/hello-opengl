#pragma once
#include <GLFW/glfw3.h>
#include "Camera.h"

// Handles mouse/scroll/keyboard input to control the Camera.
class InputHandler {
public:
    explicit InputHandler(Camera& cam) : cam_(cam) {}

    void attach(GLFWwindow* w);

    // Call once per frame to update internal state (if needed)
    void update(float /*dt*/) {}

    // GLFW callbacks (should be wired to the window)
    void onCursorPos(double x, double y);
    void onMouseButton(int button, int action, int mods);
    void onScroll(double xoffset, double yoffset);
    void onKey(int key, int scancode, int action, int mods);

private:
    Camera& cam_;
    GLFWwindow* window_ = nullptr;

    bool lmbDown_ = false;
    bool rmbDown_ = false;

    double lastX_ = 0.0;
    double lastY_ = 0.0;

    // Sensitivities
    float orbitSpeed_ = 0.008f;
    float panSpeed_   = 0.01f;
    float zoomFactor_ = 1.1f;
};
