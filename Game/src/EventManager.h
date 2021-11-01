#pragma once

#include "Camera.h"
#include <GLFW/glfw3.h>

class EventManager
{
public:
	void ProcessInputs(GLFWwindow *window, Camera &camera, float deltaTime);
};