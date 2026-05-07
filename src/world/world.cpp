#include "world.hpp"
#include "world/chunk.hpp"
#include "world/generator.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_int2.hpp>
#include <minecraft.hpp>
#include <render/opengl.hpp>
#include <world/block.hpp>
#include <world/blockregistry.hpp>
#include <util/block.hpp>
#include <render/mesh.hpp>
#include <util/block.hpp>
#include <util/file.hpp>

World::World() : generator(0) {}
World::~World() {}

void World::init() {
    shader = Shader::loadFromGLSL(readFile("assets/minecraft/shaders/mesh.vsh"), readFile("assets/minecraft/shaders/mesh.fsh"));
}

void World::render(glm::mat4 projview) {
    Minecraft* mc = Minecraft::getInstance();

    OpenGL::enableDepth();
    OpenGL::enableCulling();

    for (auto& [_, chunk] : chunks) {
        if (chunk.mesh == nullptr) continue;

        BlockEntry entry = mc->blockRegistry.get(1);

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(chunk.position.x * CHUNK_WIDTH, 0, chunk.position.y * CHUNK_DEPTH));

        shader->use();
        entry.texture->bind(0);

        shader->setUniform("model", model);
        shader->setUniform("projview", projview);

        chunk.mesh->draw();
    }

    OpenGL::disableDepth();
    OpenGL::disableCulling();
}

void World::generateChunk(glm::ivec2 pos) {
    glm::ivec3 baseBlockPos(
        pos.x * CHUNK_WIDTH,
        0,
        pos.y * CHUNK_DEPTH
    );

    Chunk chunk;

    int size = CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH;

    for (int i = 0; i < size; i++) {
        glm::ivec3 localPos = Chunk::toPosition(i);
        glm::ivec3 worldPos = baseBlockPos + localPos;

        chunk.blocks[i] = generator.getBlock(worldPos);
    }

    chunk.position = pos;
    chunks[pos] = chunk;
    chunks[pos].rebuildMesh();
}

void World::generate(int seed) {
    generator = Generator(seed);

    for (int z = 0; z < size.y; z++) {
        for (int x = 0; x < size.x; x++) {
            generateChunk(glm::ivec2(x, z));
        }
    }
}

Block World::getBlock(glm::ivec3 pos) {
    if (!inBounds(pos)) return Block(0);

    int cx = std::floor((float)pos.x / CHUNK_WIDTH);
    int cz = std::floor((float)pos.z / CHUNK_DEPTH);
    glm::ivec2 chunkKey(cx, cz);

    auto it = chunks.find(chunkKey);
    if (it == chunks.end()) {
        return Block(0);
    }

    int lx = pos.x % CHUNK_WIDTH;
    int lz = pos.z % CHUNK_DEPTH;

    if (lx < 0) lx += CHUNK_WIDTH;
    if (lz < 0) lz += CHUNK_DEPTH;

    return it->second.getBlock({lx, pos.y, lz});
}

bool World::isSolid(glm::ivec3 pos) {
    return getBlock(pos).id != 0;
}

bool World::inBounds(glm::ivec3 pos) {
    return pos.x >= 0 && pos.x < size.x * CHUNK_WIDTH &&
            pos.y >= 0 && pos.y < CHUNK_HEIGHT &&
            pos.z >= 0 && pos.z < size.y * CHUNK_DEPTH;
}