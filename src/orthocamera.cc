#include "orthocamera.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 OrthoCamera::getViewMatrix() {
    return glm::lookAt(_eye, _center, _up);
}

glm::mat4 OrthoCamera::getOrthoMatrix() {
    return glm::ortho(_xmin, _xmax, _ymin, _ymax, _nearClip, _farClip);
}