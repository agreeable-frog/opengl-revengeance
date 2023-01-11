#pragma once

#include <glm/glm.hpp>

class OrthoCamera {
public:
    glm::mat4 getViewMatrix();
    glm::mat4 getOrthoMatrix();
    OrthoCamera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up, float xmin,
                float xmax, float ymin, float ymax, float nearClip, float farClip)
        : _center(center),
          _eye(eye),
          _up(up),
          _xmin(xmin),
          _xmax(xmax),
          _ymin(ymin),
          _ymax(ymax),
          _nearClip(nearClip),
          _farClip(farClip) {};

private:
    glm::vec3 _center;
    glm::vec3 _eye;
    glm::vec3 _up;

    float _xmin;
    float _xmax;
    float _ymin;
    float _ymax;
    float _nearClip;
    float _farClip;
};