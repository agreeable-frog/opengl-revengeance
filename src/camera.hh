#pragma once

#include <glm/glm.hpp>

class Camera {
public:
    enum MOVE_DIR { FRONT = 0, BACK = 1, LEFT = 2, RIGHT = 3, UP = 4, DOWN = 5 };
    glm::mat4 getViewMatrix();
    glm::mat4 getPerspectiveMatrix(float ratio);
    Camera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up, float fov,
           float nearClip, float farClip)
        : _eye(eye),
          _center(center),
          _axis(glm::normalize(up)),
          _up(glm::normalize(up)),
          _fov(fov),
          _nearClip(nearClip),
          _farClip(farClip){};
    void move(Camera::MOVE_DIR moveDir, float deltaTime, float speed);
    void rotate(double xAxisMove, double yAxisMove, float speed);
    glm::vec3 getFront();
    glm::vec3 getPosition() const {
        return _eye;
    }

private:
    glm::vec3 _eye;
    glm::vec3 _center;
    glm::vec3 _axis;
    glm::vec3 _up;

    float _fov;
    float _nearClip;
    float _farClip;
};