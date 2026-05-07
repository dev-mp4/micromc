#ifndef MICROMC_BLOCK_HPP
#define MICROMC_BLOCK_HPP

#include <render/mesh.hpp>

class Block {
public:
    Block(unsigned int id);
    Block();
    ~Block();

    unsigned int id;
};

#endif // MICROMC_BLOCK_HPP