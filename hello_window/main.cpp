#include <glad/gl.h>
#include <GLFW/glfw3.h> 
#include <iostream> 


void processInput(GLFWwindow *window)
{

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        std::cout << "Key Pressed\n";
        glfwSetWindowShouldClose(window, true); 
    }
}




int main()
{

    glfwInit(); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Window", NULL, NULL); 

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW Window" << std::endl; 
        glfwTerminate(); 
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Inicializar GLAD 
    
    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cerr << "Failde to initialize GLAD\n";
        return -1;
    }

        //glViewport(0, 0, 400, 300);  // This in what change the behaviour? 
       

    while(!glfwWindowShouldClose(window))
    {
        
        //input 
        processInput(window); 

        // Rendering commands 

        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        

        // check and call events and swap the buffers 
        glfwSwapBuffers(window); 
        glfwPollEvents();

        //glfwTerminate();
    }
    
    return 0;

}



