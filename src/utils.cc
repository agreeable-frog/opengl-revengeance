#include "utils.hh"

#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* setupContext(int windowWidth, int windowHeight, const std::string& windowName) {
    glfwInit();

    GLFWwindow* pWindow = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), 0, 0);
    if (pWindow == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 0;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetFramebufferSizeCallback(pWindow, framebufferSizeCallback);
    glfwMakeContextCurrent(pWindow);

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glClearColor(0.1, 0.1, 0.1, 0.0);

    glewInit();
    if (!GLEW_ARB_direct_state_access) {
        std::cerr << "Direct state access not available\n";
        glfwTerminate();
        return 0;
    }
    glfwSwapInterval(1);
    return pWindow;
}

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