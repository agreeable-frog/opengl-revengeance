#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
GLFWwindow* setupContext(int windowWidth, int windowHeight, const std::string& windowName);
void testOpenglError();
void registerDebugCallbacks();