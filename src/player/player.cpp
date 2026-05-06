#include "player.hpp"
#include "minecraft.hpp"
#include "object/entitytransform.hpp"
#include <GLFW/glfw3.h>
#include <glm/common.hpp>

Player::Player() {}
Player::~Player() {}

void Player::update() {
    transform.update();

    Minecraft* mc = Minecraft::getInstance();

    if (mc->input.getKeyDown(GLFW_KEY_TAB)) {
        mouseLocked = !mouseLocked;
        mc->window.setCursorState(!mouseLocked);
    }

    if (!mouseLocked) return;

    if (mc->input.getKey(GLFW_KEY_W)) {
        transform.position += transform.forward * speed * mc->deltaTime;
    }
    if (mc->input.getKey(GLFW_KEY_S)) {
        transform.position += -transform.forward * speed * mc->deltaTime;
    }
    if (mc->input.getKey(GLFW_KEY_D)) {
        transform.position += transform.right * speed * mc->deltaTime;
    }
    if (mc->input.getKey(GLFW_KEY_A)) {
        transform.position += -transform.right * speed * mc->deltaTime;
    }

    glm::vec2 mouseDelta = Minecraft::getInstance()->input.getMouseDelta();

    rotationX -= mouseDelta.y * sensitivity;
    rotationY -= mouseDelta.x * sensitivity;

    rotationX = glm::clamp(rotationX, -90.0f, 90.0f);

    transform.rotation = EntityTransform::fromEulerAngles(glm::vec3(rotationX, rotationY, 0.0f));
}