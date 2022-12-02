#pragma once

#include <glm/glm.hpp>

#include "mesh.hh"

class Object {
public:
    Object(const Mesh& mesh, const glm::vec3& pos, float scale)
        : _mesh(mesh), _pos(pos), _scale(scale) {
        static uint32_t uid = 0;
        _id = ++uid;
    }
    const Mesh& _mesh;
    glm::vec3 _pos;
    float _scale;
    uint32_t _id;
};