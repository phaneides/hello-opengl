#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera2D {
public:
    glm::vec2 position = glm::vec2(0.0f, 0.0f);
    float zoom = 1.0f;

    float zoomSpeed = 0.1f;

    glm::mat4 getMatrix() const;

    // Para interacción con mouse:
    bool dragging = false;
    glm::vec2 lastMousePos = glm::vec2(0.0f);
};

// Para soporte de teclado si aún lo usas
void processInput(GLFWwindow* window, Camera2D& camera);

// DECLARACIONES DE CALLBACKS DE MOUSE:
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

#endif
