#include "blockregistry.hpp"

BlockRegistry::BlockRegistry() {}
BlockRegistry::~BlockRegistry() {}

void BlockRegistry::add(BlockEntry entry) {
    registry[entry.id] = entry;
}

BlockEntry BlockRegistry::get(unsigned int id) {
    return registry[id];
}