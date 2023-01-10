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
    glm::vec2 uvs;

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
        attributeDescriptions[2].size = 2;
        attributeDescriptions[2].type = GL_FLOAT;
        attributeDescriptions[2].offset = offsetof(MeshVertex, uvs);

        return attributeDescriptions;
    }
};

struct InstanceVertex {
    glm::mat4 modelMatrix;
    glm::vec3 albedo;

    static VertexBindingDescription getBindingDescription() {
        VertexBindingDescription bindingDescription{};
        bindingDescription.binding = 1;
        bindingDescription.stride = sizeof(InstanceVertex);
        bindingDescription.divisor = 1;
        return bindingDescription;
    }

    static std::array<VertexAttributeDescription, 5> getAttributeDescriptions() {
        std::array<VertexAttributeDescription, 5> attributeDescriptions{};
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
    PointLightUniform() {};
    struct Position {
        Position() = default;
        Position(float a, float b, float c) : value({a, b, c}) {};
        Position(const glm::vec3& pos) : value(pos) {};
        glm::vec3 value = glm::vec3(0.0f);
        float pad = 0.0f;
    };
    Position pos[16];
    struct Color {
        Color() = default;
        Color(float a, float b, float c) : value({a, b, c}) {};
        Color(const glm::vec3& color) : value(color){};
        glm::vec3 value = glm::vec3(0.0f);
        float pad = 0.0f;
    };
    Color color[16];
    struct Intensity {
        Intensity() = default;
        Intensity(float intensity) : value(intensity){};
        float value = 0.0f;
        glm::vec3 pad = glm::vec3(0.0f);
    };
    Intensity intensity[16];
    float count;
    static uint32_t getBindingIndex() {
        return 1;
    }
};