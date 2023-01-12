#include "snowfield.hh"

#include <vector>
#include <iostream>

Mesh Snowfield::getBaseMesh() {
    auto& center = this->_center;
    auto& up = this->_up;
    auto& forward = this->_forward;
    auto& left = this->_left;
    std::vector<MeshVertex> vertices;
    vertices.push_back({-0.5f * _length * forward + (-0.5f) * _width * left, up, {0.0f, 0.0f}});
    vertices.push_back({-0.5f * _length * forward + (0.5f) * _width * left, up, {0.0f, 0.0f}});
    vertices.push_back({0.5f * _length * forward + (0.5f) * _width * left, up, {0.0f, 0.0f}});
    vertices.push_back({0.5f * _length * forward + (-0.5f) * _width * left, up, {0.0f, 0.0f}});
    std::vector<uint32_t> indices = {0, 3, 1, 1, 3, 2, 0, 1, 3, 1, 2, 3};
    return Mesh(vertices, indices);
}

Mesh Snowfield::getFieldMesh() {
    std::vector<MeshVertex> vertices;
    std::vector<uint32_t> indices;
    uint subdiv = 10;
    for (uint i = 0; i < subdiv; i++) {
        for (uint j = 0; j < subdiv; j++) {
            static uint index = 0;
            glm::vec3 origin =
                ((-_forward * _length / 2.0f) + _forward * _length * (i / (float)subdiv)) +
                ((-_left * _width / 2.0f) + _left * _width * (j / (float)subdiv));
            vertices.push_back({origin, _up, {(i / (float)subdiv), (j / (float)subdiv)}});
            vertices.push_back({origin + _forward * _length / (float)subdiv,
                                _up,
                                {((i + 1) / (float)subdiv), (j / (float)subdiv)}});
            vertices.push_back({origin + _left * _width / (float)subdiv,
                                _up,
                                {(i / (float)subdiv), ((j + 1) / (float)subdiv)}});
            vertices.push_back(
                {origin + _forward * _length / (float)subdiv + _left * _width / (float)subdiv,
                 _up,
                 {(i + 1) / (float)subdiv, (j + 1) / (float)subdiv}});
            std::vector<uint32_t> subIndices = {index++, index++, index++, index++};
            indices.insert(indices.end(), subIndices.begin(), subIndices.end());
        }
    }
    return Mesh(vertices, indices);
}

void Snowfield::updateHeightMap(std::vector<GLfloat> *depth) {
    for (size_t i = 0; i < _heightmap.size(); i++)
    {
        GLfloat &pix = _heightmap[i];
        pix = std::min(pix, (*depth)[i]);
    }

    _heightmap_texture.fill(_heightmap);
}