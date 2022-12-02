#include "camera.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::getPerspectiveMatrix(float ratio) {
    return glm::perspective(_fov, ratio, _nearClip, _farClip);
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(_eye, _center, _up);
}