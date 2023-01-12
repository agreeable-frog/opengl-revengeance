#include "object.hh"

void updatePhysics(std::vector<Object> &objects, float dt) {
    for (Object &o : objects) {

        o._pos += o._velocity * dt;
    }
}