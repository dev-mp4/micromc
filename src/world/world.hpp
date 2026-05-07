#ifndef MICROMC_WORLD_HPP
#define MICROMC_WORLD_HPP

#include "world/generator.hpp"
#include <world/chunk.hpp>
#include <render/mesh.hpp>
#include <render/shader.hpp>
#include <world/block.hpp>
#include <glm/glm.hpp>

class World {
public:
    World();
    ~World();

    std::unordered_map<glm::ivec2, Chunk> chunks;

    glm::ivec2 size = glm::ivec2(10, 10);

    void render(glm::mat4 projview);
    void init();
    void generateChunk(glm::ivec2 pos);
    void generate(int seed);

    Block getBlock(glm::ivec3 pos);
    bool isSolid(glm::ivec3 pos);
    bool inBounds(glm::ivec3 pos);

    Generator generator;

private:
    Shader* shader;
};

#endif // MICROMC_WORLD_HPP