#include "minecraft.hpp"
#include "loader/png.hpp"
#include "render/opengl.hpp"
#include "render/texture.hpp"
#include "window.hpp"
#include "world/blockregistry.hpp"
#include <GLFW/glfw3.h>
#include <player/player.hpp>
#include <stdexcept>
#include <random>

int randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

glm::ivec3 indexToCoord(int i, int sizeX, int sizeY, int sizeZ) {
    int x = i % sizeX;
    int y = (i / sizeX) % sizeY;
    int z = i / (sizeX * sizeY);
    return {x, y, z};
}

Minecraft* Minecraft::instance;

Minecraft::Minecraft() : camera(75.0f, nullptr) {
    instance = this;

    if (!window.init("Minecraft 2.0", 1280, 720, false)) {
        throw std::runtime_error("Error happened!");
    }
    input.init(window);

    OpenGL::init(1280, 720);

    camera.window = &window;
    player.transform.position = glm::vec3(0, 0, 1);
    
    for (int i = 0; i < world.size.x * world.size.y * world.size.z; i++) {
        Block block {(unsigned int) randomInt(0, 1)};
        block.transform.position = indexToCoord(i, world.size.x, world.size.y, world.size.z);
        world.blocks.push_back(block);
    }

    world.init();

    blockRegistry.add(BlockEntry {0, nullptr}); // air

    Texture* stone = Texture::loadFromImage(PNG::loadFromFile("assets/minecraft/textures/blocks/stone.png"));
    blockRegistry.add(BlockEntry {1, stone});
}

Minecraft::~Minecraft() {
    instance = nullptr;

    window.destroy();
    input.destroy();
}

Minecraft* Minecraft::getInstance() {
    return instance;
}

void Minecraft::update() {
    time = Window::getTime();
    deltaTime = time - lastTime;
    lastTime = time;

    input.poll();

    if (input.getKeyDown(GLFW_KEY_F2)) OpenGL::toggleWireframe();

    running = running && !window.shouldClose();

    OpenGL::clear(0.55f, 0.9f, 1.0f);

    player.update();

    world.render(camera.getProjView(player.transform));
    
    window.update();
}

void Minecraft::run() {
    while (running) {
        update();
    }
}

void Minecraft::destroy() {
    input.destroy();
    window.destroy();
}