#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uvs;
layout(location = 3) in mat4 model;
layout(location = 7) in vec3 albedo;

layout(location = 0) out vec3 out_normal;
layout(location = 1) out vec2 out_uvs;
layout(location = 2) out mat4 out_model;

void main()
{
    out_normal = normal;
    out_uvs = uvs;
    out_model = model;
    gl_Position = vec4(pos, 1.0);
}