#include "utils.hh"

#include <iostream>

void testOpenglError() {
    GLenum err = glGetError();
    switch (err) {
        case GL_NO_ERROR:
            return;
        case GL_INVALID_ENUM:
            std::cerr << "GL_INVALID_ENUM\n";
            break;
        case GL_INVALID_VALUE:
            std::cerr << "GL_INVALID_VALUE\n";
            break;
        case GL_INVALID_OPERATION:
            std::cerr << "GL_INVALID_OPERATION\n";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION\n";
            break;
        case GL_OUT_OF_MEMORY:
            std::cerr << "GL_OUT_OF_MEMORY\n";
            break;
        case GL_STACK_UNDERFLOW:
            std::cerr << "GL_STACK_UNDERFLOW\n";
            break;
        case GL_STACK_OVERFLOW:
            std::cerr << "GL_STACK_OVERFLOW\n";
            break;
        default:
            std::cerr << "UNKONWN ERROR\n";
            break;
    }
}

static void debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                   const GLchar* message, const void* userparam) {
    std::cout << "DEBUG : source " << source << ", type " << type << ", id " << id << ", severity "
              << severity << '\n';
    std::cout << std::string(message) << '\n';
}

static void glfwErrorCallback(int i, const char* errStr) {
    std::cerr << "GLFW Error: " << errStr << '\n';
}

void registerDebugCallbacks() {
    glDebugMessageCallback(debugCallback, 0);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glfwSetErrorCallback(glfwErrorCallback);
}