#pragma once

#include <glm/glm.hpp>

#include "mesh.hh"

class Object {
public:
    Object(Mesh& mesh, const glm::vec3& pos, float scale, glm::vec3 albedo)
        : _mesh(mesh),
          _pos(pos),
          _scale(scale),
          _albedo(albedo) {
        static uint32_t uid = 0;
        _id = ++uid;
    }
    Mesh& _mesh;
    glm::vec3 _pos;
    float _scale;
    glm::vec3 _albedo;
    uint32_t _id;
};