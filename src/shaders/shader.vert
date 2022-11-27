#version 450

layout(location = 0) in vec3 coords;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
layout(location = 3) in mat4 model;

layout(std140, binding = 0) uniform uCamera {
    mat4 view;
    mat4 proj;
} camera;

layout(location = 0) out vec3 fNormal;

void main() {
    fNormal = color;
    gl_Position = camera.proj * camera.view * model * vec4(coords, 1.0);
}