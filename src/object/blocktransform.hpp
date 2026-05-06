#ifndef MICROMC_BLOCKTRANSFORM_HPP
#define MICROMC_BLOCKTRANSFORM_HPP

#include <glm/glm.hpp>

class BlockTransform {
public:
    BlockTransform();
    ~BlockTransform();

    glm::ivec3 position = glm::ivec3(0);

    glm::mat4 getMatrix();
};

#endif // MICROMC_BLOCKTRANSFORM_HPP