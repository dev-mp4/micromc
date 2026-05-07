#include "generator.hpp"
#include <world/block.hpp>

Generator::Generator(int seed) : seed(seed) {}
Generator::~Generator() {}

Block Generator::getBlock(glm::ivec3 pos) {
    Block block{1}; // start as stone

    if (pos.y > 6) block.id = 3;
    if (pos.y == 9) block.id = 2;

    return block;
}