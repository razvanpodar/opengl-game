#include "Game.h"

const char* vShaderPath = "shaders/shader.vs";
const char* fShaderPath = "shaders/shader.fs";
const char* vLightShaderPath = "shaders/lightShader.vs";
const char* fLightShaderPath = "shaders/lightShader.fs";
const char* vLightSourceShaderPath = "shaders/lightSourceShader.vs";
const char* fLightSourceShaderPath = "shaders/lightSourceShader.fs";
const char* vModelLoadingShaderPath = "shaders/modelLoadingShader.vs";
const char* fModelLoadingShaderPath = "shaders/modelLoadingShader.fs";

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// delta time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


int main()
{
    GLFWwindow* window;

    // Initialize the library 
    if (!glfwInit())
        return -1;

    // Choose OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Init GLEW after creating a GLFW context
    glewInit();

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Initialize
    EventManager eventManager;
    TextureManager textureManager;
    //Shader shader(vShaderPath, fShaderPath);
    Shader shader(vModelLoadingShaderPath, fModelLoadingShaderPath);
    Shader lightShader(vLightShaderPath, fLightShaderPath);
    Shader lightSourceShader(vLightSourceShaderPath, fLightSourceShaderPath);

    // Temporary - will be moved to some classes

    glm::vec3 cubePositions[] = { glm::vec3(0.0f,  0.0f,  0.0f),
                                    glm::vec3(2.0f,  5.0f, -15.0f),
                                    glm::vec3(-1.5f, -2.2f, -2.5f),
                                    glm::vec3(-3.8f, -2.0f, -12.3f),
                                    glm::vec3(2.4f, -0.4f, -3.5f),
                                    glm::vec3(-1.7f,  3.0f, -7.5f),
                                    glm::vec3(1.3f, -2.0f, -2.5f),
                                    glm::vec3(1.5f,  2.0f, -2.5f),
                                    glm::vec3(1.5f,  0.2f, -1.5f),
                                    glm::vec3(-1.3f,  1.0f, -1.5f) };

    Model cube("res/tex_cube.obj");
    Model plane("res/plane.obj");

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Inputs
        eventManager.ProcessInputs(window, camera, deltaTime);

        // Render here
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        shader.SetUniform3fv("viewPos", camera.m_position);
        shader.SetUniform3fv("objectColor", glm::vec3(0.3f, 0.2f, 0.6f));

        // Update transformations matrices
        glm::mat4 projection = glm::perspective(glm::radians(camera.m_zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.SetUniformMatrix4fv("projection", projection);

        glm::mat4 view = camera.GetViewMatrix();
        shader.SetUniformMatrix4fv("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        shader.SetUniformMatrix4fv("model", model);

        plane.Draw(shader);

        cube.Draw(shader);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    //glDeleteVertexArrays(1, &VAO);
    shader.Delete();
    lightShader.Delete();
    lightSourceShader.Delete();

    glfwTerminate();

	return 0;
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
