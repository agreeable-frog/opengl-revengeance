#pragma once

#include "object.hh"

#include <glm/glm.hpp>
#include <vector>
#include <list>

class HeightMapTexture {
public:
    HeightMapTexture(uint width, uint height);
    ~HeightMapTexture();

    void fill(std::vector<float> data);
    void bind(uint layout);

private:
    uint _width;
    uint _height;
    GLuint _handle;
};