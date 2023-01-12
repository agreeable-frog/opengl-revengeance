#version 450

layout(quads, equal_spacing, ccw) in;

layout(location = 0) in vec3 normal[];
layout(location = 1) in vec2 uvs[];
layout(location = 2) in mat4 model[];

layout(location = 0) out vec3 out_normal;

layout(binding = 0) uniform sampler2D heightmap;

layout(location = 0) uniform float depth;

layout(std140, binding = 0) uniform uCamera {
    mat4 view;
    mat4 proj;
    vec3 pos;
} camera;

void main() {
    vec2 patchUvs = gl_TessCoord.xy;
    vec2 t00 = uvs[0];
    vec2 t01 = uvs[1];
    vec2 t10 = uvs[2];
    vec2 t11 = uvs[3];

    vec2 t0 = mix(t00, t01, patchUvs.x);
    vec2 t1 = mix(t10, t11, patchUvs.x);
    vec2 texCoord = mix(t0, t1, patchUvs.y);
    texCoord.x = 1.0 - texCoord.x;

    float height = texture(heightmap, texCoord).x;

    vec4 p00 = gl_in[0].gl_Position;
    vec4 p01 = gl_in[1].gl_Position;
    vec4 p10 = gl_in[2].gl_Position;
    vec4 p11 = gl_in[3].gl_Position;

    vec4 p0 = mix(p00, p01, patchUvs.x);
    vec4 p1 = mix(p10, p11, patchUvs.x);
    vec4 p = mix(p0, p1, patchUvs.y);

    p += vec4(normal[0], 0.0) * (height * depth);

    out_normal = normal[0];

    gl_Position =  camera.proj * camera.view * model[0] * p;
}