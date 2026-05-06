#ifndef MICROMC_MESH_HPP
#define MICROMC_MESH_HPP

#include <vector>

class Mesh {
public:
    Mesh(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int indicesCount);
    ~Mesh();

    void draw();
    static Mesh* create(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned char>& attributes);
    void destroy();

private:
    unsigned int vao, vbo, ebo, indicesCount;
};

#endif //MICROMC_MESH_HPP