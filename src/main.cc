#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "mesh.hh"
#include "object.hh"
#include "program.hh"
#include "utils.hh"
#include "datastructs.hh"
#include "inputs.hh"
#include "camera.hh"

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

int main() {
    // SETUP
    GLFWwindow* pWindow = setupContext(640, 480, "window");
    registerDebugCallbacks();
    if (!pWindow) return 1;
    auto program = Program();
    program.loadShaders("src/shaders/shader.vert", "src/shaders/shader.frag");
    program.linkProgram();

    // SCENE CREATION
    std::vector<MeshVertex> vertices = {};
    std::vector<uint32_t> indices = {};
    std::vector<InstanceVertex> instanceVertices = {};

    std::cout << "hello\n";

    auto cubeMesh = CubeMesh();
    auto sphereMesh = SphereMesh(128, 128);

    cubeMesh.loadIntoBuffer(vertices, indices);
    sphereMesh.loadIntoBuffer(vertices, indices);

    std::vector<Object> scene;
    scene.push_back({cubeMesh, {0.0, 0.0, 0.0}, 1.0});
    scene.push_back({cubeMesh, {0.0, 3.0, 0.0}, 1.0});
    scene.push_back({sphereMesh, {-2.0, 1.0, 0.0}, 1.0});

    int width, height;
    glfwGetFramebufferSize(pWindow, &width, &height);

    Camera cam = {glm::vec3{-5.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                  glm::vec3{0.0f, 1.0f, 0.0f}, (float)M_PI_2, 1.0f, 20.0f};
    auto camU = CameraUniform{};
    auto lightU = PointLightUniform{};
    lightU.pos = glm::vec3{-10.0, 10.0, 10.0};
    lightU.intensity = 100;
    lightU.color = glm::vec3{1.0, 1.0, 1.0};
    camU.projMatrix = cam.getPerspectiveMatrix((float)width / (float)height);
    camU.viewMatrix = cam.getViewMatrix();

    // BUFFERS CREATION
    GLuint vertexBuffer;
    GLuint indexBuffer;
    GLuint instanceBuffer;
    glCreateBuffers(1, &vertexBuffer);
    glCreateBuffers(1, &indexBuffer);
    glCreateBuffers(1, &instanceBuffer);
    glNamedBufferData(vertexBuffer, vertices.size() * sizeof(MeshVertex), vertices.data(),
                      GL_STATIC_DRAW);
    glNamedBufferData(indexBuffer, indices.size() * sizeof(uint32_t), indices.data(),
                      GL_STATIC_DRAW);

    GLuint uboCamera;
    glCreateBuffers(1, &uboCamera);
    glNamedBufferData(uboCamera, sizeof(camU), &camU, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, camU.getBindingIndex(), uboCamera);
    glBindBufferRange(GL_UNIFORM_BUFFER, camU.getBindingIndex(), uboCamera, 0, sizeof(CameraUniform));

    GLuint uboLight;
    glCreateBuffers(1, &uboLight);
    glNamedBufferData(uboLight, sizeof(lightU), &lightU, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, lightU.getBindingIndex(), uboLight);
    glBindBufferRange(GL_UNIFORM_BUFFER, lightU.getBindingIndex(), uboLight, 0, sizeof(PointLightUniform));

    // ATTRIBUTES DECLARATION
    GLuint objectsVao;
    glCreateVertexArrays(1, &objectsVao);

    auto vertexBindingDescription = MeshVertex::getBindingDescription();
    glVertexArrayVertexBuffer(objectsVao, vertexBindingDescription.binding, vertexBuffer, 0,
                              vertexBindingDescription.stride);
    glVertexArrayElementBuffer(objectsVao, indexBuffer);
    for (auto vertexAttributeDescription : MeshVertex::getAttributeDescriptions()) {
        glVertexArrayAttribBinding(objectsVao, vertexAttributeDescription.location,
                                   vertexBindingDescription.binding);
        glVertexArrayAttribFormat(objectsVao, vertexAttributeDescription.location,
                                  vertexAttributeDescription.size, vertexAttributeDescription.type,
                                  false, vertexAttributeDescription.offset);
        glEnableVertexArrayAttrib(objectsVao, vertexAttributeDescription.location);
    }

    auto instanceBindingDescription = InstanceVertex::getBindingDescription();
    glVertexArrayVertexBuffer(objectsVao, instanceBindingDescription.binding, instanceBuffer, 0,
                              instanceBindingDescription.stride);
    glVertexArrayBindingDivisor(objectsVao, instanceBindingDescription.binding,
                                instanceBindingDescription.divisor);
    for (auto instanceAttributeDescription : InstanceVertex::getAttributeDescriptions()) {
        glVertexArrayAttribBinding(objectsVao, instanceAttributeDescription.location,
                                   instanceBindingDescription.binding);
        glVertexArrayAttribFormat(
            objectsVao, instanceAttributeDescription.location, instanceAttributeDescription.size,
            instanceAttributeDescription.type, false, instanceAttributeDescription.offset);
        glEnableVertexArrayAttrib(objectsVao, instanceAttributeDescription.location);
    }

    // DRAW

    std::map<Mesh, std::vector<Object>> instanceGroups;
    for (Object object : scene) {
        instanceGroups[object._mesh].push_back(object);
    }
    std::cout << "scene description : \n";
    std::cout << "number of different meshes in scene : " << instanceGroups.size() << '\n';
    std::cout << "objects for each mesh : \n";
    for (auto& [key, value] : instanceGroups) {
        std::cout << "mesh " << key._id << " : " << value.size() << " objects\n";
    }

    glUseProgram(program.programId);
    registerInputFunctions(pWindow);

    double lastFrame = glfwGetTime();
    while (!glfwWindowShouldClose(pWindow)) {

        double currentFrame = glfwGetTime();
        float ellapsedTime = (currentFrame - lastFrame);
        lastFrame = currentFrame;

        glfwGetFramebufferSize(pWindow, &width, &height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        double mousePos[2] = {0};
        glfwGetCursorPos(pWindow, mousePos, mousePos + 1);
        mousePos[0] = (width / 2) - mousePos[0];
        mousePos[1] = mousePos[1] - (height / 2);
        moveCamera(ellapsedTime, cam, mousePos);
        glfwSetCursorPos(pWindow, width / 2, height / 2);
        camU.projMatrix = cam.getPerspectiveMatrix((float)width / (float)height);
        camU.viewMatrix = cam.getViewMatrix();
        glNamedBufferData(uboCamera, sizeof(camU), &camU, GL_DYNAMIC_DRAW);
        glBindVertexArray(objectsVao);
        std::map<Mesh, std::vector<Object>> instanceGroups;
        for (Object object : scene) {
            instanceGroups[object._mesh].push_back(object);
        }
        for (const auto& [key, value] : instanceGroups) {
            instanceVertices = {};
            for (auto& object : value) {
                auto modelMatrix = glm::mat4(1.0);
                modelMatrix = glm::translate(modelMatrix, object._pos);
                modelMatrix = glm::scale(modelMatrix, glm::vec3(object._scale));
                instanceVertices.push_back({modelMatrix});
            }
            glNamedBufferData(instanceBuffer, instanceVertices.size() * sizeof(InstanceVertex),
                              instanceVertices.data(), GL_STREAM_DRAW);
            glDrawElementsInstanced(GL_TRIANGLES, key.getIndicesCount(), GL_UNSIGNED_INT,
                                    (void*)key.getIndexBufferOffset(), instanceVertices.size());
        }
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }
    glfwDestroyWindow(pWindow);
    glfwTerminate();
    return 0;
}