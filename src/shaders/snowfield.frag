#version 450

layout(location = 0) in vec3 normal;

layout(location = 0) out vec4 outFragColor;

#define MAX_NB_LIGHTS 16

layout(std140, binding = 1) uniform uLight {
    vec3 pos[MAX_NB_LIGHTS];
    vec3 color[MAX_NB_LIGHTS];
    float intensity[MAX_NB_LIGHTS];
    float count;
} light;

void main() {
    outFragColor = vec4(0.0, 0.7, 0.0, 1.0);
}