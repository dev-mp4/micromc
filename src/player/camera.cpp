#include "camera.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

Camera::Camera(float fov, Window* window, float farPlane) : fov(fov), window(window), farPlane(farPlane) {}
Camera::~Camera() {}

glm::mat4 Camera::getProjView(EntityTransform transform) {
    glm::mat4 projection = glm::perspective(glm::radians(fov), (float) window->getWidth() / (float) window->getHeight(), 0.01f, farPlane);

    return projection * glm::inverse(transform.getMatrix());
}