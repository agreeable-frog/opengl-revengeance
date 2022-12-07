#pragma once

#include <array>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct VertexBindingDescription {
    GLuint binding;
    GLsizei stride;
    GLuint divisor;
};

struct VertexAttributeDescription {
    GLuint location;
    GLint size;
    GLenum type;
    size_t offset;
};

struct MeshVertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec3 color;

    static VertexBindingDescription getBindingDescription() {
        VertexBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(MeshVertex);
        bindingDescription.divisor = 0;
        return bindingDescription;
    }

    static std::array<VertexAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VertexAttributeDescription, 3> attributeDescriptions{};
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].size = 3;
        attributeDescriptions[0].type = GL_FLOAT;
        attributeDescriptions[0].offset = offsetof(MeshVertex, pos);

        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].size = 3;
        attributeDescriptions[1].type = GL_FLOAT;
        attributeDescriptions[1].offset = offsetof(MeshVertex, normal);

        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].size = 3;
        attributeDescriptions[2].type = GL_FLOAT;
        attributeDescriptions[2].offset = offsetof(MeshVertex, color);

        return attributeDescriptions;
    }
};

struct InstanceVertex {
    glm::mat4 modelMatrix;
    glm::vec3 albedo;
    float roughness;
    float metallic;

    static VertexBindingDescription getBindingDescription() {
        VertexBindingDescription bindingDescription{};
        bindingDescription.binding = 1;
        bindingDescription.stride = sizeof(InstanceVertex);
        bindingDescription.divisor = 1;
        return bindingDescription;
    }

    static std::array<VertexAttributeDescription, 7> getAttributeDescriptions() {
        std::array<VertexAttributeDescription, 7> attributeDescriptions{};
        attributeDescriptions[0].location = 3;
        attributeDescriptions[0].size = 4;
        attributeDescriptions[0].type = GL_FLOAT;
        attributeDescriptions[0].offset = 0;

        attributeDescriptions[1].location = 4;
        attributeDescriptions[1].size = 4;
        attributeDescriptions[1].type = GL_FLOAT;
        attributeDescriptions[1].offset = sizeof(GLfloat) * 4;

        attributeDescriptions[2].location = 5;
        attributeDescriptions[2].size = 4;
        attributeDescriptions[2].type = GL_FLOAT;
        attributeDescriptions[2].offset = sizeof(GLfloat) * 8;

        attributeDescriptions[3].location = 6;
        attributeDescriptions[3].size = 4;
        attributeDescriptions[3].type = GL_FLOAT;
        attributeDescriptions[3].offset = sizeof(GLfloat) * 12;

        attributeDescriptions[4].location = 7;
        attributeDescriptions[4].size = 3;
        attributeDescriptions[4].type = GL_FLOAT;
        attributeDescriptions[4].offset = offsetof(InstanceVertex, albedo);

        attributeDescriptions[5].location = 8;
        attributeDescriptions[5].size = 1;
        attributeDescriptions[5].type = GL_FLOAT;
        attributeDescriptions[5].offset = offsetof(InstanceVertex, roughness);

        attributeDescriptions[6].location = 9;
        attributeDescriptions[6].size = 1;
        attributeDescriptions[6].type = GL_FLOAT;
        attributeDescriptions[6].offset = offsetof(InstanceVertex, metallic);

        return attributeDescriptions;
    }
};

struct CameraUniform {
    alignas(16) glm::mat4 viewMatrix;
    alignas(16) glm::mat4 projMatrix;
    alignas(4) glm::vec3 pos;
    static uint32_t getBindingIndex() {
        return 0;
    }
};

struct PointLightUniform {
    glm::vec4 pos[16];
    glm::vec4 color[16];
    glm::vec4 intensity[16];
    float count;
    static uint32_t getBindingIndex() {
        return 1;
    }
};