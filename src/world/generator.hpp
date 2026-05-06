#ifndef MICROMC_GENERATOR_HPP
#define MICROMC_GENERATOR_HPP

#include <world/block.hpp>

class Generator {
public:
    Generator(int seed);
    ~Generator();

    Block getBlock(glm::ivec3 pos);

    int seed;
};

#endif // MICROMC_GENERATOR_HPP