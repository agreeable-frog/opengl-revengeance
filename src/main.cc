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
#include "scene.hh"

int main() {
    // SETUP
    GLFWwindow* pWindow = setupContext(640, 480, "window");
    registerDebugCallbacks();
    if (!pWindow) return 1;
    auto program = Program();
    program.loadShaders("src/shaders/shader.vert", "src/shaders/shader.frag");
    program.linkProgram();

    // SCENE CREATION
    auto scene = Scene();
    std::vector<MeshVertex> vertices = {};
    std::vector<uint32_t> indices = {};
    std::vector<InstanceVertex> instanceVertices = {};

    auto cubeMesh = CubeMesh();
    auto sphereMesh = SphereMesh(128, 128);

    cubeMesh.loadIntoBuffer(vertices, indices);
    sphereMesh.loadIntoBuffer(vertices, indices);

    scene._objects.push_back({cubeMesh, {0.0, 0.0, 0.0}, 1.0, {1.0, 0.0, 0.0}, 1.0, 0.0});
    scene._objects.push_back({cubeMesh, {0.0, 3.0, 0.0}, 1.0, {0.0, 1.0, 0.0}, 1.0, 0.0});
    scene._objects.push_back({sphereMesh, {-2.0, 1.0, 0.0}, 1.0, {0.0, 0.0, 1.0}, 1.0, 0.0});

    scene._camera = {glm::vec3{-5.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                                  glm::vec3{0.0f, 1.0f, 0.0f}, (float)M_PI_2, 1.0f, 20.0f};
    auto camU = CameraUniform{};
    auto lightU = PointLightUniform{};
    lightU.pos[0] = glm::vec4{-10.0, 10.0, 10.0, 0.0};
    lightU.intensity[0] = glm::vec4{100.0, 0.0, 0.0, 0.0};
    lightU.color[0] = glm::vec4{1.0, 1.0, 1.0, 0.0};
    lightU.count = 1;

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
    for (Object object : scene._objects) {
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

        int width, height;
        glfwGetFramebufferSize(pWindow, &width, &height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        double mousePos[2] = {0};
        glfwGetCursorPos(pWindow, mousePos, mousePos + 1);
        mousePos[0] = (width / 2) - mousePos[0];
        mousePos[1] = mousePos[1] - (height / 2);
        moveCamera(ellapsedTime, scene._camera, mousePos);
        glfwSetCursorPos(pWindow, width / 2, height / 2);
        camU.projMatrix = scene._camera.getPerspectiveMatrix((float)width / (float)height);
        camU.viewMatrix = scene._camera.getViewMatrix();
        camU.pos = scene._camera.getPosition();
        glNamedBufferData(uboCamera, sizeof(camU), &camU, GL_DYNAMIC_DRAW);
        glBindVertexArray(objectsVao);
        std::map<Mesh, std::vector<Object>> instanceGroups;
        for (Object object : scene._objects) {
            instanceGroups[object._mesh].push_back(object);
        }
        for (const auto& [key, value] : instanceGroups) {
            instanceVertices = {};
            for (auto& object : value) {
                auto modelMatrix = glm::translate(glm::mat4(1.0), object._pos);
                modelMatrix = glm::scale(modelMatrix, glm::vec3(object._scale));
                instanceVertices.push_back({modelMatrix, object._albedo, object._roughness, object._metallic});
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