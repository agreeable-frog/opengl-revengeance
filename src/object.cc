#include "object.hh"

#define G -0.981

void updatePhysics(std::vector<Object> &objects, float dt) {
    for (Object &o : objects) {
        o._velocity += glm::vec3(0, G * dt, 0);

        o._pos += o._velocity;

        if (o._pos.y < 0) {
            o._pos.y = 0;
            o._velocity.y = -o._velocity.y / 2;
        }
    }
}