#pragma once

#include <glm/glm.hpp>

class Camera {
public:
    glm::mat4 getViewMatrix();
    glm::mat4 getPerspectiveMatrix(float ratio);
    Camera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up, float fov,
           float nearClip, float farClip)
        : _eye(eye),
          _center(center),
          _axis(up),
          _up(up),
          _fov(fov),
          _nearClip(nearClip),
          _farClip(farClip){};

private:
    glm::vec3 _eye;
    glm::vec3 _center;
    const glm::vec3 _axis;
    glm::vec3 _up;

    float _fov;
    float _nearClip;
    float _farClip;
};