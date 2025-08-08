#include "Input.h"

static InputHandler* g_input_for_callbacks = nullptr;

// Static trampoline functions for GLFW to forward to our instance
static void s_cursorPos(GLFWwindow* w, double x, double y) {
    if (g_input_for_callbacks) g_input_for_callbacks->onCursorPos(x, y);
}
static void s_mouseButton(GLFWwindow* w, int button, int action, int mods) {
    if (g_input_for_callbacks) g_input_for_callbacks->onMouseButton(button, action, mods);
}
static void s_scroll(GLFWwindow* w, double xoff, double yoff) {
    if (g_input_for_callbacks) g_input_for_callbacks->onScroll(xoff, yoff);
}
static void s_key(GLFWwindow* w, int key, int scancode, int action, int mods) {
    if (g_input_for_callbacks) g_input_for_callbacks->onKey(key, scancode, action, mods);
}

void InputHandler::attach(GLFWwindow* w) {
    window_ = w;
    g_input_for_callbacks = this;
    glfwSetCursorPosCallback(w, s_cursorPos);
    glfwSetMouseButtonCallback(w, s_mouseButton);
    glfwSetScrollCallback(w, s_scroll);
    glfwSetKeyCallback(w, s_key);

    // Initialize last cursor position
    double x, y; glfwGetCursorPos(w, &x, &y);
    lastX_ = x; lastY_ = y;
}

void InputHandler::onCursorPos(double x, double y) {
    double dx = x - lastX_;
    double dy = y - lastY_;
    lastX_ = x; lastY_ = y;

    if (lmbDown_ && !rmbDown_) {
        // Orbit: LMB drag
        cam_.orbit((float)(dx * orbitSpeed_), (float)(-dy * orbitSpeed_));
    } else if (rmbDown_ && !lmbDown_) {
        // Pan: RMB drag (scale pan by current radius a bit)
        float scale = cam_.radius * panSpeed_;
        cam_.pan((float)(dx * scale), (float)(-dy * scale));
    }
}

void InputHandler::onMouseButton(int button, int action, int /*mods*/) {
    if (button == GLFW_MOUSE_BUTTON_LEFT)  lmbDown_ = (action == GLFW_PRESS);
    if (button == GLFW_MOUSE_BUTTON_RIGHT) rmbDown_ = (action == GLFW_PRESS);
}

void InputHandler::onScroll(double /*xoffset*/, double yoffset) {
    if (yoffset > 0) cam_.zoom(1.0f/zoomFactor_);
    if (yoffset < 0) cam_.zoom(zoomFactor_);
}

void InputHandler::onKey(int key, int /*scancode*/, int action, int /*mods*/) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_R) {
            // Reset camera
            cam_.center = {0,0,0};
            cam_.yaw = 0.785398163f;
            cam_.pitch = 0.6f;
            cam_.radius = 16.0f;
        }
    }
}
