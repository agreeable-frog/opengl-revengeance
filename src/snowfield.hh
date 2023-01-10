#pragma once

#include "object.hh"
#include "heightmap_texture.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <list>

class Snowfield {
public:
    glm::vec3 _center;
    glm::vec3 _up;
    float _height;
    glm::vec3 _forward;
    float _length;
    glm::vec3 _left;
    float _width;
    std::list<float> _heightmap_data;
    HeightMapTexture _heightmap_texture;
    uint _heightmapLength;
    uint _heightmapWidth;

    Snowfield(const glm::vec3& center, const glm::vec3& up, float height, const glm::vec3& forward,
              float length, float width)
        : _center(center),
          _up(glm::normalize(up)),
          _height(height),
          _forward(glm::normalize(forward)),
          _length(length),
          _left(glm::cross(_up, _forward)),
          _width(width),
          _heightmap_texture(width, length){};

    Mesh getBaseMesh();
    Mesh getFieldMesh();
};