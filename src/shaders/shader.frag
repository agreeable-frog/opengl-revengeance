#version 450

#define MAX_NB_LIGHTS 16
#define M_PI 3.141592

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 albedo;

layout(location = 0) out vec4 outFragColor;

layout(std140, binding = 0) uniform uCamera {
    mat4 view;
    mat4 proj;
    vec3 pos;
}
camera;

layout(std140, binding = 1) uniform uLight {
    vec3 pos[MAX_NB_LIGHTS];
    vec3 color[MAX_NB_LIGHTS];
    float intensity[MAX_NB_LIGHTS];
    float count;
}
light;

void main() {
    outFragColor.rgba = vec4(albedo, 1.0);
}