#ifndef MICROMC_WORLD_HPP
#define MICROMC_WORLD_HPP

#include <render/mesh.hpp>
#include <render/shader.hpp>
#include <vector>
#include <world/block.hpp>
#include <glm/glm.hpp>

class World {
public:
    World();
    ~World();

    std::vector<Block> blocks;

    glm::ivec3 size = glm::ivec3(100, 10, 100);

    void render(glm::mat4 projview);
    void init();
    void generate(int seed);

    Block getBlock(glm::ivec3 pos);
    bool isSolid(glm::ivec3 pos);
    int toIndex(glm::ivec3 pos);
    glm::ivec3 toPosition(int index);
    bool inBounds(glm::ivec3 pos);

    void rebuildMeshes();

private:
    Shader* shader;
};

#endif // MICROMC_WORLD_HPP