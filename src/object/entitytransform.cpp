#include "entitytransform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

EntityTransform::EntityTransform() {}
EntityTransform::~EntityTransform() {}

void EntityTransform::update() {
    forward = glm::normalize(rotation * glm::vec3(0, 0, -1));
    up      = glm::normalize(rotation * glm::vec3(0, 1,  0));
    right   = glm::normalize(rotation * glm::vec3(1, 0,  0));

    glm::vec3 yzx = glm::eulerAngles(rotation);
    eulerAngles = glm::vec3(yzx.z, yzx.x, yzx.y);
}

glm::mat4 EntityTransform::getMatrix() {
    glm::mat4 matrix(1.0);
    matrix = glm::translate(matrix, position);

    glm::mat4 rotMatrix = glm::toMat4(rotation);
    matrix *= rotMatrix;

    matrix = glm::scale(matrix, scale);

    return matrix;
}

glm::quat EntityTransform::fromEulerAngles(glm::vec3 angles) {
    return glm::quat(glm::radians(angles));
}