#pragma once

#include "camera.hh"
#include "snowfield.hh"

void moveCamera(float deltaTime, Camera& camera, double mousePos[2]);
void regenerateRandomSnowfield(float currentFrame, Snowfield& snowfield);
void registerInputFunctions(GLFWwindow* pWindow);
