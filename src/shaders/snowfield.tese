#version 450

layout(quads, equal_spacing, ccw) in;

layout(location = 0) in vec3 normal[];
layout(location = 1) in vec2 uvs[];
layout(location = 2) in mat4 model[];

layout(location = 0) out vec3 out_normal;

layout(binding = 0) uniform sampler2D heightmap;

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

    vec2 t0 = (t01 - t00) * patchUvs.x + t00;
    vec2 t1 = (t11 - t10) * patchUvs.x + t10;
    vec2 texCoord = (t1 - t0) * patchUvs.y + t0;

    float height = texture(heightmap, texCoord).x;

    vec4 p00 = gl_in[0].gl_Position;
    vec4 p01 = gl_in[1].gl_Position;
    vec4 p10 = gl_in[2].gl_Position;
    vec4 p11 = gl_in[3].gl_Position;

    vec4 p0 = (p01 - p00) * patchUvs.x + p00;
    vec4 p1 = (p11 - p10) * patchUvs.x + p10;
    vec4 p = (p1 - p0) * patchUvs.y + p0;

    p += vec4(normal[0], 0.0) * (height + 0.01);

    out_normal = normal[0];

    gl_Position =  camera.proj * camera.view * model[0] * p;
}