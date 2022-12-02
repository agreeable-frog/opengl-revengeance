#include "camera.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

glm::mat4 Camera::getPerspectiveMatrix(float ratio) {
    return glm::perspective(_fov, ratio, _nearClip, _farClip);
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(_eye, _center, _up);
}

glm::vec3 Camera::getFront() {
    return glm::normalize(_center - _eye);
}

void Camera::move(Camera::MOVE_DIR moveDir, float deltaTime, float speed) {
    auto front = getFront();
    auto left = glm::cross(_up, front);
    std::vector<glm::vec3> moves = {front, -front, left, -left, _axis, -_axis};
    _eye += 10.0f * speed * deltaTime * moves[moveDir];
    _center += 10.0f * speed * deltaTime * moves[moveDir];
}

static glm::mat4 getRotMatrix(const glm::vec3& axis, float angle, const glm::vec3& origin) {
    auto translateMatrix = glm::translate(glm::mat4(1.0f), -origin);
    auto translateMatrixBack = glm::translate(glm::mat4(1.0f), origin);
    auto rotMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
    return translateMatrixBack * rotMatrix * translateMatrix;
}

void Camera::rotate(double xAxisMove, double yAxisMove, float speed) {
    if (!(xAxisMove || yAxisMove)) return;

    static double yAxisMoveLimiter = 0;
    if (std::abs(yAxisMoveLimiter + yAxisMove) < 200) {
        yAxisMoveLimiter += yAxisMove;
        auto left = glm::normalize(glm::cross(_up, getFront()));
        _center = getRotMatrix(left, yAxisMove * speed / 100.0f, _eye) * glm::vec4(_center, 1.0f);
        _up = glm::normalize(
            glm::vec3(getRotMatrix(left, yAxisMove * speed / 100.0f, {0.0f, 0.0f, 0.0f}) *
                      glm::vec4(_up, 1.0f)));
    }
    _center = getRotMatrix(_axis, xAxisMove * speed / 100.0f, _eye) * glm::vec4(_center, 1.0f);
    _up = glm::normalize(
        glm::vec3(getRotMatrix(_axis, xAxisMove * speed / 100.0f, {0.0f, 0.0f, 0.0f}) *
                  glm::vec4(_up, 1.0f)));
}