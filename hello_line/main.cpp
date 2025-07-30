
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "camera.hpp" // << Aquí usamos tu clase de cámara

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Cargar shaders desde archivo
std::string loadShaderSource(const char* filePath) {
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int compileShader(unsigned int type, const char* source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "Shader compilation error:\n" << log << std::endl;
    }
    return shader;
}

unsigned int createShaderProgram(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode = loadShaderSource(vertexPath);
    std::string fragmentCode = loadShaderSource(fragmentPath);
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode.c_str());
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Línea con Cámara 2D", nullptr, nullptr);
    if (!window) {
        std::cerr << "No se pudo crear la ventana GLFW\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "No se pudo inicializar GLAD\n";
        return -1;
    }

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // posiciones
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    unsigned int shaderProgram = createShaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");

    Camera2D camera;

    while (!glfwWindowShouldClose(window)) {

        glfwSetWindowUserPointer(window, &camera);
        //CallBacks
        //processInput(window, camera); // mover cámara

        glfwSetScrollCallback(window, scroll_callback);
        glfwSetCursorPosCallback(window, cursor_position_callback);
        glfwSetMouseButtonCallback(window, mouse_button_callback);  

        glClearColor(0.08f, 0.08f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::mat4 MVP = camera.getMatrix();
        int mvpLoc = glGetUniformLocation(shaderProgram, "MVP");
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(MVP));

        glBindVertexArray(VAO);
        glLineWidth(3.0f);
        glDrawArrays(GL_LINES, 0, 2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
