#ifndef MICROMC_CHUNK_HPP
#define MICROMC_CHUNK_HPP

#include <glm/glm.hpp>
#include <render/mesh.hpp>
#include <world/block.hpp>

#define CHUNK_HEIGHT 32
#define CHUNK_WIDTH 16
#define CHUNK_DEPTH 16

namespace std {
    template<>
    struct hash<glm::ivec2> {
        std::size_t operator()(const glm::ivec2& p) const noexcept {
            std::size_t hx = std::hash<int>{}(p.x);
            std::size_t hz = std::hash<int>{}(p.y);

            return hx ^ (hz << 1);
        }
    };
}

class Chunk {
public:
    Chunk();
    ~Chunk();

    std::vector<Block> blocks;

    Block getBlock(glm::ivec3 pos);
    bool isSolid(glm::ivec3 pos);
    bool inBounds(glm::ivec3 pos);

    void rebuildMesh();

    static int toIndex(glm::ivec3 pos);
    static glm::ivec3 toPosition(int index);

    glm::ivec2 position;
    Mesh* mesh;
};

#endif // MICROMC_CHUNK_HPP