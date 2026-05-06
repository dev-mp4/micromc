#ifndef MICROMC_CAMERA_HPP
#define MICROMC_CAMERA_HPP

#include <object/entitytransform.hpp>
#include <window.hpp>

class Camera {
public:
    Camera(float fov, Window* window);
    ~Camera();

    glm::mat4 getProjView(EntityTransform transform);

    float fov;

    Window* window;
};

#endif // MICROMC_CAMERA_HPP