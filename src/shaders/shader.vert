#version 450

#define MAX_NB_LIGHTS 16

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
layout(location = 3) in mat4 model;
layout(location = 7) in vec3 albedo;
layout(location = 8) in float roughness;
layout(location = 9) in float metallic;

layout(std140, binding = 0) uniform uCamera {
    mat4 view;
    mat4 proj;
    vec3 pos;
} camera;

layout(std140, binding = 1) uniform uLight {
    vec4 pos[MAX_NB_LIGHTS];
    vec4 color[MAX_NB_LIGHTS];
    vec4 intensity[MAX_NB_LIGHTS];
    float count;
} light;

layout(location = 0) out vec3 outPos;
layout(location = 1) out vec3 outNormal;
layout(location = 2) out vec3 outAlbedo;
layout(location = 3) out float outRoughness;
layout(location = 4) out float outMetallic;

void main() {
    gl_Position = camera.proj * camera.view * model * vec4(pos, 1.0);

    outNormal = (model * vec4(normal, 1.0)).xyz;
    outPos = (model * vec4(pos, 1.0)).xyz;
    outAlbedo = albedo;
    outRoughness = roughness;
    outMetallic = metallic;
}