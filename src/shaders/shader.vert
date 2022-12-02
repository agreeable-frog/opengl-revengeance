#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
layout(location = 3) in mat4 model;

layout(std140, binding = 0) uniform uCamera {
    mat4 view;
    mat4 proj;
} camera;

layout(std140, binding = 1) uniform uLight {
    vec3 pos;
    float intensity;
    vec3 color;
} light;

layout(location = 0) out vec3 fColor;

void main() {
    gl_Position = camera.proj * camera.view * model * vec4(pos, 1.0);

    vec3 lightDir = light.pos - pos;
    fColor = color * clamp(dot(lightDir, normal), 0., 1.);
}