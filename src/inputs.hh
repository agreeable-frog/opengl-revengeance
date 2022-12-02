#pragma once

#include <GLFW/glfw3.h>

#include "camera.hh"

void moveCamera(float deltaTime, Camera& camera, double mousePos[2]);
void registerInputFunctions(GLFWwindow* pWindow);
