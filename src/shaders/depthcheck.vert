#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uvs;
layout(location = 3) in mat4 model;
layout(location = 7) in vec3 albedo;

layout(std140, binding = 0) uniform uCamera {
    mat4 view;
    mat4 proj;
    vec3 pos;
} camera;

void main() {
    gl_Position = camera.proj * camera.view * model * vec4(pos, 1.0);
}