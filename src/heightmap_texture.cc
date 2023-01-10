#include "heightmap_texture.hh"

HeightMapTexture::HeightMapTexture(uint width, uint height)  :
    _width(width),
    _height(height) {
    glCreateTextures(GL_TEXTURE_2D, 1, &_handle);

    glTextureStorage2D(_handle, 0, GL_DEPTH_COMPONENT32, _width, _height);
}

HeightMapTexture::~HeightMapTexture() {
    glDeleteTextures(1, &_handle);
}

void HeightMapTexture::fill(std::vector<float> data) {
    glTextureSubImage2D(_handle, 0, 0, 0, _width, _height, GL_DEPTH_COMPONENT, GL_FLOAT, data.data());
}

void HeightMapTexture::bind(uint layout) {
    glBindTextureUnit(layout, _handle);
}