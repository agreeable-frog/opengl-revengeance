#include "mesh.hh"

#include <algorithm>

void Mesh::loadIntoBuffer(std::vector<MeshVertex>& vertexBuffer, std::vector<uint32_t>& indexBuffer) {
    _vertexBufferOffset = vertexBuffer.size();
    _indicesCount = _indices.size();
    _indexBufferOffset = indexBuffer.size() * sizeof(uint32_t);

    vertexBuffer.insert(vertexBuffer.end(), _vertices.begin(), _vertices.end());
    std::vector<uint32_t> indicesOffsetted = std::vector<uint32_t>(_indices.size());
    std::transform(_indices.begin(), _indices.end(), indicesOffsetted.begin(),
                   [&, this](uint32_t i) { return i + _vertexBufferOffset; });
    indexBuffer.insert(indexBuffer.end(), indicesOffsetted.begin(), indicesOffsetted.end());
}

CubeMesh::CubeMesh() : Mesh::Mesh() {
    _vertices.push_back(MeshVertex{{-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}});
    _vertices.push_back(MeshVertex{{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}});
    _vertices.push_back(MeshVertex{{1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}});
    _vertices.push_back(MeshVertex{{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}});
    std::vector<uint16_t> indexFace1 = {0, 1, 3, 1, 2, 3};
    _indices.insert(_indices.end(), indexFace1.begin(), indexFace1.end());

    _vertices.push_back(MeshVertex{{-1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}});
    _vertices.push_back(MeshVertex{{-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}});
    _vertices.push_back(MeshVertex{{1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}});
    _vertices.push_back(MeshVertex{{1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}});
    std::vector<uint16_t> indexFace2 = {4, 5, 7, 5, 6, 7};
    _indices.insert(_indices.end(), indexFace2.begin(), indexFace2.end());

    _vertices.push_back(MeshVertex{{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, 1.0f}});
    _vertices.push_back(MeshVertex{{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, 1.0f}});
    _vertices.push_back(MeshVertex{{1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, 1.0f}});
    _vertices.push_back(MeshVertex{{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, 1.0f}});
    std::vector<uint16_t> indexFace3 = {8, 9, 11, 9, 10, 11};
    _indices.insert(_indices.end(), indexFace3.begin(), indexFace3.end());

    _vertices.push_back(MeshVertex{{-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}});
    _vertices.push_back(MeshVertex{{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}});
    _vertices.push_back(MeshVertex{{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}});
    _vertices.push_back(MeshVertex{{1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}});
    std::vector<uint16_t> indexFace4 = {12, 13, 15, 13, 14, 15};
    _indices.insert(_indices.end(), indexFace4.begin(), indexFace4.end());

    _vertices.push_back(MeshVertex{{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}});
    _vertices.push_back(MeshVertex{{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}});
    _vertices.push_back(MeshVertex{{1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}});
    _vertices.push_back(MeshVertex{{1.0f, 1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}});
    std::vector<uint16_t> indexFace5 = {16, 17, 19, 17, 18, 19};
    _indices.insert(_indices.end(), indexFace5.begin(), indexFace5.end());

    _vertices.push_back(MeshVertex{{-1.0f, 1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 1.0f}});
    _vertices.push_back(MeshVertex{{-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 1.0f}});
    _vertices.push_back(MeshVertex{{-1.0f, -1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 1.0f}});
    _vertices.push_back(MeshVertex{{-1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 1.0f}});
    std::vector<uint16_t> indexFace6 = {20, 21, 23, 21, 22, 23};
    _indices.insert(_indices.end(), indexFace6.begin(), indexFace6.end());
}

SphereMesh::SphereMesh(size_t nRings, size_t nSegments) : Mesh::Mesh() {
    _vertices.push_back(MeshVertex{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
                              glm::vec3(1.0f, 0.0f, 0.0f)});
    for (size_t h = 0; h < nRings; h++) {
        float theta = (h + 1) * M_PI / (nRings + 1);
        for (size_t v = 0; v < nSegments; v++) {
            float phi = v * 2 * M_PI / (nSegments);
            float x = std::sin(theta) * std::cos(phi);
            float y = std::sin(theta) * std::sin(phi);
            float z = std::cos(theta);
            _vertices.push_back(
                MeshVertex{glm::vec3(x, y, z), glm::vec3(x, y, z), glm::vec3(1.0f, 0.0f, 0.0f)});
        }
    }
    _vertices.push_back(MeshVertex{glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f),
                              glm::vec3(1.0f, 0.0f, 0.0f)});
    // cap
    /*
     *             x
     *          * * * *
     *       *   *   *   *
     *    *     *     *     *
     * x       x       x       x
     */
    for (size_t i = 0; i < nSegments; i++) {
        _indices.push_back(0);
        _indices.push_back(i + 1);
        _indices.push_back(((i + 1) % nSegments) + 1);
    }

    // body
    /*
     *     x----x----x----x
     *    *      *    *
     *   *    *        *    *
     *  *    *          *    *
     * x-----x----------x-----x
     * *     *          *     *
     * *     *          *     *
     * x-----x----------x-----x
     *  *    *          *    *
     *   *    *        *    *
     *    *    *      *    *
     *     x----x----x----x
     */
    for (size_t i = 0; i < nRings - 1; i++) {
        for (size_t j = 0; j < nSegments; j++) {
            size_t k = 1 + i * nSegments + j;
            size_t knext = 1 + i * nSegments + ((j + 1) % nSegments);

            _indices.push_back(k);
            _indices.push_back(k + nSegments);
            _indices.push_back(knext + nSegments);

            _indices.push_back(knext + nSegments);
            _indices.push_back(knext);
            _indices.push_back(k);
        }
    }

    // keel
    /*
     * x       x       x       x
     *    *     *     *     *
     *       *   *   *   *
     *          * * * *
     *             x
     */
    for (size_t i = 0; i < nSegments; i++) {
        size_t lastRingFirstIndex = (nRings - 1) * nSegments + 1;
        _indices.push_back(lastRingFirstIndex + i);
        _indices.push_back(_vertices.size() - 1);
        _indices.push_back(lastRingFirstIndex + ((i + 1) % nSegments));
    }
}