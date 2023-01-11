#include "inputs.hh"

#include <vector>
#include <cstdlib>

int KEYSTATES[512] = {0};

static void keyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        KEYSTATES[key] = 1;
    }
    if (action == GLFW_RELEASE) {
        KEYSTATES[key] = 0;
    }
}

void registerInputFunctions(GLFWwindow* pWindow) {
    // glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    // prevents missing key events but often cause them to be registered 2 times
    // should not be a problem most of the time
    glfwSetKeyCallback(pWindow, keyCallback);

    glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported()) glfwSetInputMode(pWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

void regenerateRandomSnowfield(float currentFrame, Snowfield& snowfield) {
    static float lastFrame = 0.0f;
    if (KEYSTATES[GLFW_KEY_R] == 1) {
        if ((currentFrame - lastFrame) > 0.1f) {
            lastFrame = currentFrame;
        } else {
            return;
        }
        std::vector<float> map = std::vector<float>(
            snowfield._heightmap_texture._height * snowfield._heightmap_texture._width, 0.0f);
        for (size_t i = 0; i < snowfield._heightmap_texture._height; i++) {
            for (size_t j = 0; j < snowfield._heightmap_texture._width; j++) {
                map[i * snowfield._heightmap_texture._width + j] = (float)(rand() % 1000) / 1000.0f;
            }
        }
        snowfield._heightmap_texture.fill(map);
    }
}

void moveCamera(float deltaTime, Camera& camera, double mouseMove[2]) {
    if (KEYSTATES[GLFW_KEY_W] == 1) {
        camera.move(Camera::MOVE_DIR::FRONT, deltaTime, 1.0f);
    }
    if (KEYSTATES[GLFW_KEY_A] == 1) {
        camera.move(Camera::MOVE_DIR::LEFT, deltaTime, 1.0f);
    }
    if (KEYSTATES[GLFW_KEY_S] == 1) {
        camera.move(Camera::MOVE_DIR::BACK, deltaTime, 1.0f);
    }
    if (KEYSTATES[GLFW_KEY_D] == 1) {
        camera.move(Camera::MOVE_DIR::RIGHT, deltaTime, 1.0f);
    }
    if (KEYSTATES[GLFW_KEY_C] == 1) {
        camera.move(Camera::MOVE_DIR::DOWN, deltaTime, 1.8f);
    }
    if (KEYSTATES[GLFW_KEY_SPACE] == 1) {
        camera.move(Camera::MOVE_DIR::UP, deltaTime, 1.8f);
    }
    camera.rotate(mouseMove[0], mouseMove[1], 0.5f);
}