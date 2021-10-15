#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
    GLFWwindow* window;

    // Initialize the library 
    if (!glfwInit())
        return -1;

    glewInit();

    // Choose OpenGL version
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render here 
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

	return 0;
}
