#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "datastructs.hh"

class Mesh {
protected:
    std::vector<MeshVertex> _vertices;
    std::vector<uint32_t> _indices;
    uint32_t _vertexBufferOffset;
    size_t _indexBufferOffset;
    uint32_t _indicesCount;

public:
    uint32_t _id;
    Mesh();
    Mesh(std::vector<MeshVertex> vertices, std::vector<uint32_t> indices);
    uint32_t getVertexBufferOffset() const {
        return _vertexBufferOffset;
    };
    size_t getIndexBufferOffset() const {
        return _indexBufferOffset;
    };
    uint32_t getIndicesCount() const {
        return _indicesCount;
    };
    void loadIntoBuffer(std::vector<MeshVertex>& vertexBuffer, std::vector<uint32_t>& indexBuffer);
};

namespace std // dont ask an explanation from me there
{
    template<> struct less<Mesh>
    {
       bool operator() (const Mesh& lhs, const Mesh& rhs) const
       {
           return lhs._id < rhs._id;
       }
    };
}

class CubeMesh : public Mesh {
public:
    CubeMesh();
};

class SphereMesh : public Mesh {
public:
    SphereMesh(size_t nRings, size_t nSegments);
};