#ifndef MICROMC_MINECRAFT_HPP
#define MICROMC_MINECRAFT_HPP

#include "player/camera.hpp"
#include "player/player.hpp"
#include "world/blockregistry.hpp"
#include "world/world.hpp"
#include <input.hpp>
#include <window.hpp>

class Minecraft {
public:
    Minecraft();
    ~Minecraft();

    static Minecraft* getInstance();

    Window window;
    Input input;

    Player player;
    Camera camera;
    World world;

    BlockRegistry blockRegistry;

    void update();

    void run();

    void destroy();

    bool running;

    float time;
    float deltaTime;
    float lastTime;

private:
    static Minecraft* instance;

};

#endif // MICROMC_MINECRAFT_HPP