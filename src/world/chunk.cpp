#include "chunk.hpp"
#include "minecraft.hpp"
#include <cstddef>
#include <vector>
#include <world/block.hpp>
#include <util/block.hpp>

void addFace(std::vector<float>& dst,
             const std::array<float, 30>& src,
             glm::ivec3 pos)
{
    for (int i = 0; i < 30; i += 5) {

        float x = src[i + 0] + pos.x;
        float y = src[i + 1] + pos.y;
        float z = src[i + 2] + pos.z;

        float u = src[i + 3];
        float v = src[i + 4];

        dst.push_back(x);
        dst.push_back(y);
        dst.push_back(z);
        dst.push_back(u);
        dst.push_back(v);
    }
}

constexpr glm::ivec3 dirs[6] = {
    { 0,  0,  1}, // front
    { 0,  0, -1}, // back
    {-1,  0,  0}, // left
    { 1,  0,  0}, // right
    { 0,  1,  0}, // top
    { 0, -1,  0}  // bottom
};

Chunk::Chunk() : mesh(nullptr) {
    blocks.resize(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH);
    for (int i = 0; i < CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH; i++) {
        blocks[i] = Block(0); // air
    }
}

Chunk::~Chunk() {}

Block Chunk::getBlock(glm::ivec3 pos) {
    if (inBounds(pos)) return blocks[toIndex(pos)];
    return Block();
}

bool Chunk::isSolid(glm::ivec3 pos) {
    return getBlock(pos).id != 0;
}

bool Chunk::inBounds(glm::ivec3 pos) {
    return pos.x >= 0 && pos.x < CHUNK_WIDTH &&
            pos.y >= 0 && pos.y < CHUNK_HEIGHT &&
            pos.z >= 0 && pos.z < CHUNK_DEPTH;
}

int Chunk::toIndex(glm::ivec3 pos) {
    return pos.x + CHUNK_WIDTH * (pos.y + CHUNK_HEIGHT * pos.z);
}

glm::ivec3 Chunk::toPosition(int index) {
    int x = index % CHUNK_WIDTH;
    int y = (index / CHUNK_WIDTH) % CHUNK_HEIGHT;
    int z = index / (CHUNK_WIDTH * CHUNK_HEIGHT);
    return glm::ivec3(x, y, z);
}

void Chunk::rebuildMesh() {
    std::vector<float> vertices;

    World& world = Minecraft::getInstance()->world;

    glm::ivec3 worldBase = glm::ivec3(position.x * CHUNK_WIDTH, 0, position.y * CHUNK_DEPTH);

    for (int i = 0; i < blocks.size(); i++) {
        Block block = blocks[i];
 
        if (block.id == 0) continue; // skip air

        glm::ivec3 pos = toPosition(i);
        glm::ivec3 worldPos = worldBase + pos;

        if (!world.isSolid(worldPos + dirs[0])) addFace(vertices, BLOCK_FRONT, pos);
        if (!world.isSolid(worldPos + dirs[1])) addFace(vertices, BLOCK_BACK, pos);
        if (!world.isSolid(worldPos + dirs[2])) addFace(vertices, BLOCK_LEFT, pos);
        if (!world.isSolid(worldPos + dirs[3])) addFace(vertices, BLOCK_RIGHT, pos);
        if (!world.isSolid(worldPos + dirs[4])) addFace(vertices, BLOCK_TOP, pos);
        if (!world.isSolid(worldPos + dirs[5])) addFace(vertices, BLOCK_BOTTOM, pos);

        if (vertices.size() == 0) continue; // skip covered block
    }

    if (mesh) mesh->destroy();
    mesh = Mesh::create(vertices, {}, {3, 2});
}