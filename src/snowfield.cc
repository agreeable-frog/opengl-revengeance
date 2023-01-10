#include "snowfield.hh"

#include <vector>

Mesh Snowfield::getFieldMesh() {
    auto& center = this->_center;
    auto& up = this->_up;
    auto& forward = this->_forward;
    auto& left = this->_left;
    std::vector<MeshVertex> vertices;
    vertices.push_back({-0.5f * _length * forward + (-0.5f) * _width * left, up, {1.0f, 0.0f, 0.0f}});
    vertices.push_back({-0.5f * _length * forward + (0.5f) * _width * left, up, {1.0f, 0.0f, 0.0f}});
    vertices.push_back({0.5f * _length * forward + (0.5f) * _width * left, up, {1.0f, 0.0f, 0.0f}});
    vertices.push_back({0.5f * _length * forward + (-0.5f) * _width * left, up, {1.0f, 0.0f, 0.0f}});
    std::vector<uint32_t> indices = {0, 3, 1, 1, 3, 2, 0, 1, 3, 1, 2, 3};
    return Mesh(vertices, indices);
}