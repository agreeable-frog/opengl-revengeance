#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "camera.hh"
#include "snowfield.hh"

void moveCamera(float deltaTime, Camera& camera, double mousePos[2]);
void regenerateRandomSnowfield(float currentFrame, Snowfield& snowfield);
void registerInputFunctions(GLFWwindow* pWindow);
void saveDepthBuffer(float currentFrame, std::vector<GLfloat>& depthBuffer, uint width,
                     uint height);
