
#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera2D::getMatrix() const {
    glm::mat4 projection = glm::ortho(-1.0f * zoom, 1.0f * zoom,
                                      -1.0f * zoom, 1.0f * zoom,
                                      -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-position, 0.0f));
    return projection * view;
}

// Mouse scroll → zoom

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Camera2D* camera = static_cast<Camera2D*>(glfwGetWindowUserPointer(window));
    if (camera) {
        camera->zoom *= (1.0f - yoffset * camera->zoomSpeed);
        if (camera->zoom < 0.01f) camera->zoom = 0.01f;
    }
}


// Mouse move → arrastre
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    Camera2D* camera = static_cast<Camera2D*>(glfwGetWindowUserPointer(window));
    if (!camera || !camera->dragging) return;

    glm::vec2 currentMouse = glm::vec2(xpos, ypos);
    glm::vec2 delta = currentMouse - camera->lastMousePos;
    camera->lastMousePos = currentMouse;

    float aspectRatio = 800.0f / 600.0f; // ajustar si tu ventana cambia de tamaño
    float scale = camera->zoom / 300.0f;

    camera->position -= glm::vec2(delta.x * scale * aspectRatio, -delta.y * scale);
}

// Mouse click → iniciar/finalizar arrastre
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    Camera2D* camera = static_cast<Camera2D*>(glfwGetWindowUserPointer(window));
    if (!camera) return;

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            camera->dragging = true;
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            camera->lastMousePos = glm::vec2(xpos, ypos);
        } else if (action == GLFW_RELEASE) {
            camera->dragging = false;
        }
    }
}
