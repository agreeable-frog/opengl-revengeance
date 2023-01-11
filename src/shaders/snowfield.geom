#version 450

layout(triangles) in;
layout(line_strip, max_vertices=5) out;

layout(location = 0) in vec3 normal[];

layout(location = 0) out vec3 out_normal;

void main() {
    for (int i = 0; i < 4; i++) {
        out_normal = normal[i];
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}