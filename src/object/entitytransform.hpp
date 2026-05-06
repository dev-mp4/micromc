#ifndef MICROMC_ENTITYTRANSFORM_HPP
#define MICROMC_ENTITYTRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class EntityTransform {
public:
    EntityTransform();
    ~EntityTransform();

    glm::vec3 position = glm::vec3(0);
    glm::quat rotation = glm::quat(1, 0, 0, 0);
    glm::vec3 scale = glm::vec3(1);

    glm::vec3 eulerAngles = glm::vec3(0);

    glm::vec3 forward = glm::vec3(0);
    glm::vec3 up = glm::vec3(0);
    glm::vec3 right = glm::vec3(0);

    void update();
    glm::mat4 getMatrix();

    static glm::quat fromEulerAngles(glm::vec3 angles);
};

#endif // MICROMC_ENTITYTRANSFORM_HPP