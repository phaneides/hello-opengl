#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "math/Math.h"
#include "gl/Shader.h"
#include "render/Grid.h"
#include "scene/Camera.h"
#include "scene/Input.h"

// Shaders
static const char* kVS = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 uMVP;
void main(){
    gl_Position = uMVP * vec4(aPos, 1.0);
}
)";

static const char* kFS = R"(
#version 330 core
out vec4 FragColor;
uniform vec3 uColor;
void main(){
    FragColor = vec4(uColor, 1.0);
}
)";

static void framebuffer_size_callback(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Grid + Camera (Orbit/Pan/Zoom)", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoaderLoadGL()) {
        std::cerr << "Failed to init GLAD\n";
        return -1;
    }

    // GL state
    glEnable(GL_DEPTH_TEST);
    glLineWidth(1.0f);

    // Shader and geometry
    Shader shader(kVS, kFS);
    Grid grid(20, 1.0f);

    // Camera + input
    Camera camera;
    InputHandler input(camera);
    input.attach(window);

    while (!glfwWindowShouldClose(window)) {
        int w,h; glfwGetFramebufferSize(window, &w, &h);
        float aspect = (h > 0) ? float(w)/float(h) : 1.0f;

        glClearColor(0.06f, 0.07f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Build MVP
        Mat4 P = perspective(45.0f * float(M_PI) / 180.0f, aspect, 0.1f, 100.0f);
        Mat4 V = camera.view();
        Mat4 M = Mat4::identity();
        Mat4 MVP = P * V * M;

        shader.use();
        shader.setMat4("uMVP", MVP);

        // Draw grid
        shader.setVec3("uColor", 0.55f, 0.58f, 0.65f);
        grid.drawGrid();

        // Draw axes
        shader.setVec3("uColor", 0.95f, 0.35f, 0.35f);
        grid.drawAxes();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
