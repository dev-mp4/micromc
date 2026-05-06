#ifndef MICROMC_BLOCKREGISTRY_HPP
#define MICROMC_BLOCKREGISTRY_HPP

#include <render/texture.hpp>
#include <unordered_map>

struct BlockEntry {
    unsigned int id;
    Texture* texture;
};

class BlockRegistry {
public:
    BlockRegistry();
    ~BlockRegistry();

    std::unordered_map<unsigned int, BlockEntry> registry;

    void add(BlockEntry entry);
    BlockEntry get(unsigned int id);
};

#endif // MICROMC_BLOCKREGISTRY_HPP