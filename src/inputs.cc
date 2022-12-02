#include "inputs.hh"

#include "camera.hh"

#include <GLFW/glfw3.h>

int KEYSTATES[512] = {0};

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        KEYSTATES[key] = 1;
    }
    if (action == GLFW_RELEASE) {
        KEYSTATES[key] = 0;
    }
}

void moveCamera(float deltaTime, Camera& camera) {
    
}