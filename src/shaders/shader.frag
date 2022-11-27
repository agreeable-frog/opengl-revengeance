#version 450

layout(location = 0) in vec3 normal;

layout(location = 0) out vec4 fragColor;

layout(std140, binding = 0) uniform uCamera {
    mat4 view;
    mat4 proj;
} camera;

void main() {
    fragColor = vec4(normal.r, normal.g, normal.b, 1.0);
}