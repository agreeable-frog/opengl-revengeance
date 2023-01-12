#include "object.hh"

#define G -0.0981

void updatePhysics(std::vector<Object> &objects, float dt) {
    for (size_t i = 0; i < objects.size() - 1; i++) {
        Object &o = objects[i];

        o._velocity.y += G * dt;

        o._pos += o._velocity;

        if (o._pos.y - o._scale < 0) {
            o._pos.y = o._scale;
            o._velocity.y = -o._velocity.y / 2;
            o._velocity /= 1.05f;
        }
    }
}