#pragma once

#include <glm/glm.hpp>

#include "mesh.hh"

class Object {
public:
    Object(const Mesh& mesh, const glm::vec3& pos, float scale, glm::vec3 albedo, float roughness,
           float metallic)
        : _mesh(mesh),
          _pos(pos),
          _scale(scale),
          _albedo(albedo),
          _roughness(roughness),
          _metallic(metallic) {
        static uint32_t uid = 0;
        _id = ++uid;
    }
    const Mesh& _mesh;
    glm::vec3 _pos;
    float _scale;
    glm::vec3 _albedo;
    float _roughness;
    float _metallic;
    uint32_t _id;
};