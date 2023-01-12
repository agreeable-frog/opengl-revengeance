#version 450

layout (vertices=4) out;

layout(location = 0) in vec3 normal[];
layout(location = 1) in vec2 uvs[];
layout(location = 2) in mat4 model[];

layout(location = 0) out vec3 out_normal[];
layout(location = 1) out vec2 out_uvs[];
layout(location = 2) out mat4 out_model[];

void main() {
    gl_TessLevelOuter[0] = 4;
    gl_TessLevelOuter[1] = 4;
    gl_TessLevelOuter[2] = 4;
    gl_TessLevelOuter[3] = 4;

    gl_TessLevelInner[0] = 4;
    gl_TessLevelInner[1] = 4;

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    out_normal[gl_InvocationID] = normal[gl_InvocationID];
    out_uvs[gl_InvocationID] = uvs[gl_InvocationID];
    out_model[gl_InvocationID] = model[gl_InvocationID];
}