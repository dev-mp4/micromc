#include "generator.hpp"
#include <cmath>
#include <world/block.hpp>

Generator::Generator(int seed) : seed(seed) {}
Generator::~Generator() {}

Block Generator::getBlock(glm::ivec3 pos) {
    Block block{0}; // start as air

    float frequency = 0.5f;
    float amplitude = 5.0f;
    float level = 1.0f;

    float height = std::sin(pos.x * frequency) * amplitude + level;
    if (height < 0) height = 1;

    if (pos.y <= height) {
        block.id = 1;
        block.transform.position = pos;
    }

    return block;
}