#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "object.hh"
#include "camera.hh"

class Scene {
public:
    Scene()
        : _camera({glm::vec3{-5.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f},
                   glm::vec3{0.0f, 1.0f, 0.0f}, (float)M_PI_2, 1.0f, 20.0f}){};
    std::vector<Object> _objects;
    Camera _camera;
};