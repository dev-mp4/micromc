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

    glm::ivec3 size = glm::ivec3(10, 5, 10);

    void render(glm::mat4 projview);
    void init();

    Block getBlock(glm::ivec3 pos);
    bool isSolid(glm::ivec3 pos);
    int toIndex(glm::ivec3 pos);
    bool inBounds(glm::ivec3 pos);

private:
    Shader* shader;
};

#endif // MICROMC_WORLD_HPP