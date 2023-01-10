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
#include "snowfield.hh"

int main() {
// SETUP
#pragma region SETUP
    GLFWwindow* pWindow = setupContext(640, 480, "window");
    registerDebugCallbacks();
    if (!pWindow) return 1;
    auto programBasic = Program();
    programBasic.loadShaders("src/shaders/basic.vert", "src/shaders/basic.frag");
    programBasic.linkProgram();
    auto programSnowfield = Program();
    programSnowfield.loadShaders("src/shaders/snowfield.vert", "src/shaders/snowfield.tesc",
                                 "src/shaders/snowfield.tese", "src/shaders/snowfield.frag");
    programSnowfield.linkProgram();
#pragma endregion

// SCENE CREATION
#pragma region SCENE_CREATION
    auto scene = Scene();
    std::vector<MeshVertex> vertices = {};
    std::vector<uint32_t> indices = {};
    std::vector<InstanceVertex> instanceVertices = {};

    auto cubeMesh = CubeMesh();
    auto sphereMesh = SphereMesh(128, 128);

    cubeMesh.loadIntoBuffer(vertices, indices);
    sphereMesh.loadIntoBuffer(vertices, indices);

    scene._objects.push_back({cubeMesh, {0.0f, 0.0f, 0.0f}, 1.0f, {1.0f, 0.0f, 0.0f}});

    scene._camera = {glm::vec3{-5.0f, 5.01f, 0.01f},
                     glm::vec3{0.0f, 0.0f, 0.0f},
                     glm::vec3{0.0f, 1.0f, 0.0f},
                     (float)M_PI_2,
                     1.0f,
                     20.0f};
    auto camU = CameraUniform{};
    auto lightU = PointLightUniform{};
    lightU.pos[0] = {-10.0f, 10.0f, 10.0f};
    lightU.intensity[0] = 100.0;
    lightU.color[0] = {1.0, 1.0, 1.0};
    lightU.count = 1;

    auto snowfield =
        Snowfield({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, 1.0f, {1.0f, 0.0f, 0.0f}, 5.0f, 5.0f);
    auto snowFieldBaseMesh = snowfield.getBaseMesh();
    snowFieldBaseMesh.loadIntoBuffer(vertices, indices);
    scene._objects.push_back({snowFieldBaseMesh, snowfield._center, 1.0f, {1.0f, 1.0f, 1.0f}});
    auto snowFieldMesh = snowfield.getFieldMesh();
    snowFieldMesh.loadIntoBuffer(vertices, indices);
    std::vector<float> map = std::vector<float>(100 * 100, 0.0f);
    for (size_t i = 0; i < 50; i++) {
        for (size_t j = 0; j < 50; j++) {
            map[i * 100 + j] = 1.0f;
        }
    }
    snowfield._heightmap_texture.fill(map);
#pragma endregion

// BUFFERS CREATION
#pragma region BUFFERS_CREATION
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
    glBindBufferRange(GL_UNIFORM_BUFFER, camU.getBindingIndex(), uboCamera, 0,
                      sizeof(CameraUniform));

    GLuint uboLight;
    glCreateBuffers(1, &uboLight);
    glNamedBufferData(uboLight, sizeof(lightU), &lightU, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, lightU.getBindingIndex(), uboLight);
    glBindBufferRange(GL_UNIFORM_BUFFER, lightU.getBindingIndex(), uboLight, 0,
                      sizeof(PointLightUniform));
#pragma endregion

// VERTEX SPECIFICATION
#pragma region VERTEX_SPECIFICATION
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
#pragma endregion

// DRAW
#pragma region DRAW
    registerInputFunctions(pWindow);

    double lastFrame = glfwGetTime();
    while (!glfwWindowShouldClose(pWindow)) {
        double currentFrame = glfwGetTime();
        float ellapsedTime = (currentFrame - lastFrame);
        lastFrame = currentFrame;

        int width, height;
        glfwGetFramebufferSize(pWindow, &width, &height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#pragma region CAMERA_CONTROL
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
#pragma endregion

#pragma region OBJECTS_DRAW
        glUseProgram(programBasic.programId);
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
                instanceVertices.push_back({modelMatrix, object._albedo});
            }
            glNamedBufferData(instanceBuffer, instanceVertices.size() * sizeof(InstanceVertex),
                              instanceVertices.data(), GL_STREAM_DRAW);
            glDrawElementsInstanced(GL_TRIANGLES, key.getIndicesCount(), GL_UNSIGNED_INT,
                                    (void*)key.getIndexBufferOffset(), instanceVertices.size());
        }
#pragma endregion

#pragma region DRAW_SNOWFIELD
        glUseProgram(programSnowfield.programId);
        glPatchParameteri(GL_PATCH_VERTICES, 4);
        snowfield._heightmap_texture.bind(0);
        Object object = Object(snowFieldMesh, snowfield._center, 1.0f, {1.0f, 0.0f, 0.0f});
        instanceVertices = {};
        auto modelMatrix = glm::translate(glm::mat4(1.0), object._pos);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(object._scale));
        instanceVertices.push_back({modelMatrix, object._albedo});
        //snowfield._heightmap_texture.bind(0);
        glNamedBufferData(instanceBuffer, instanceVertices.size() * sizeof(InstanceVertex),
                          instanceVertices.data(), GL_STREAM_DRAW);
        glDrawElementsInstanced(GL_PATCHES, snowFieldMesh.getIndicesCount(), GL_UNSIGNED_INT,
                                (void*)snowFieldMesh.getIndexBufferOffset(),
                                instanceVertices.size());

#pragma endregion

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }
#pragma endregion
    glfwDestroyWindow(pWindow);
    glfwTerminate();
    return 0;
}