#version 450

layout(location = 0) in vec3 color;

layout(location = 0) out vec4 outColor;

layout(std140, binding = 0) uniform uCamera {
    mat4 view;
    mat4 proj;
} camera;

void main() {
    outColor = vec4(color, 1.0);
}