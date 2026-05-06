#include "blocktransform.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

BlockTransform::BlockTransform() {}
BlockTransform::~BlockTransform() {}

glm::mat4 BlockTransform::getMatrix() {
    return glm::translate(glm::mat4(1.0f), glm::vec3(position));
}