#ifndef MICROMC_BLOCK_HPP
#define MICROMC_BLOCK_HPP

#include <object/blocktransform.hpp>

class Block {
public:
    Block(unsigned int id);
    ~Block();

    unsigned int id;

    BlockTransform transform;
};

#endif // MICROMC_BLOCK_HPP