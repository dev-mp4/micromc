#include "world.hpp"
#include "world/generator.hpp"
#include <minecraft.hpp>
#include <render/opengl.hpp>
#include <world/block.hpp>
#include <world/blockregistry.hpp>
#include <util/block.hpp>
#include <render/mesh.hpp>
#include <util/block.hpp>
#include <vector>
#include <util/file.hpp>

static const glm::ivec3 dirs[6] = {
    { 0,  0,  1}, // front
    { 0,  0, -1}, // back
    {-1,  0,  0}, // left
    { 1,  0,  0}, // right
    { 0,  1,  0}, // top
    { 0, -1,  0}  // bottom
};

World::World() {}
World::~World() {}

void addFace(std::vector<float>& dst, const std::array<float, 30>& src) {
    dst.insert(dst.end(), src.begin(), src.end());
}

void World::init() {
    shader = Shader::loadFromGLSL(readFile("assets/minecraft/shaders/mesh.vsh"), readFile("assets/minecraft/shaders/mesh.fsh"));
}

void World::render(glm::mat4 projview) {
    Minecraft* mc = Minecraft::getInstance();

    OpenGL::enableDepth();
    OpenGL::enableCulling();

    for (auto& block : blocks) {
        if (block.id == 0 || block.mesh == nullptr) continue; // skip air

        BlockEntry entry = mc->blockRegistry.get(block.id);

        shader->use();
        entry.texture->bind(0);

        shader->setUniform("model", block.transform.getMatrix());
        shader->setUniform("projview", projview);

        block.mesh->draw();
    }

    OpenGL::disableDepth();
    OpenGL::disableCulling();
}

Block World::getBlock(glm::ivec3 pos) {
    return blocks[toIndex(pos)];
}

bool World::isSolid(glm::ivec3 pos) {
    return inBounds(pos) && getBlock(pos).id != 0;
}

int World::toIndex(glm::ivec3 pos) {
    return pos.x + pos.y * size.x + pos.z * size.x * size.y;
}

bool World::inBounds(glm::ivec3 pos) {
    return pos.x >= 0 && pos.y >= 0 && pos.z >= 0 &&
           pos.x < size.x && pos.y < size.y && pos.z < size.z;
}

glm::ivec3 World::toPosition(int index) {
    int x = index % size.x;
    int y = (index / size.x) % size.y;
    int z = index / (size.x * size.y);
    return glm::ivec3(x, y, z);
}

void World::generate(int seed) {
    int blocksCount = size.x * size.y * size.z;

    Generator gen(seed);

    blocks.clear();
    blocks.reserve(blocksCount);

    for (int i = 0; i < blocksCount; i++) {
        blocks.push_back(gen.getBlock(toPosition(i)));
    }
}

void World::rebuildMeshes() {
    for (auto& block : blocks) {
        if (block.id == 0) continue; // skip air

        std::vector<float> vertices = {};

        glm::ivec3 pos = block.transform.position;

        if (!isSolid(pos + dirs[0])) addFace(vertices, BLOCK_FRONT);
        if (!isSolid(pos + dirs[1])) addFace(vertices, BLOCK_BACK);
        if (!isSolid(pos + dirs[2])) addFace(vertices, BLOCK_LEFT);
        if (!isSolid(pos + dirs[3])) addFace(vertices, BLOCK_RIGHT);
        if (!isSolid(pos + dirs[4])) addFace(vertices, BLOCK_TOP);
        if (!isSolid(pos + dirs[5])) addFace(vertices, BLOCK_BOTTOM);

        if (vertices.size() == 0) continue; // skip covered block

        std::vector<unsigned int> indices = {};

        for (int i = 0; i < vertices.size(); i++) {
            indices.push_back(i);
        }

        block.mesh = Mesh::create(vertices, indices, {3, 2});
    }
}