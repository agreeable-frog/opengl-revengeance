#pragma once

#include "object.hh"
#include "heightmap_texture.hh"
#include "orthocamera.hh"

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
    HeightMapTexture _heightmap_texture;
    OrthoCamera _camera;

    Snowfield(const glm::vec3& center, const glm::vec3& up, float height, const glm::vec3& forward,
              float length, float width, uint heightmapLength, uint heignthmapWidth)
        : _center(center),
          _up(glm::normalize(up)),
          _height(height),
          _forward(glm::normalize(forward)),
          _length(length),
          _left(glm::cross(_up, _forward)),
          _width(width),
          _heightmap_texture(heightmapLength, heignthmapWidth),
          _camera(center, _center + _up, _left, -_width / 2.0f, _width / 2.0f, -_length / 2.0f,
                  _length / 2.0f, 0.0f, _height * 10.0f){};

    Mesh getBaseMesh();
    Mesh getFieldMesh();
};