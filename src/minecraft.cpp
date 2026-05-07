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
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <string>

int randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

Minecraft* Minecraft::instance;

Minecraft::Minecraft() : camera(75.0f, nullptr), drawCalls(0) {
    instance = this;

    if (!window.init("Minecraft 2.0", 1280, 720, false)) {
        throw std::runtime_error("Error happened!");
    }
    input.init(window);

    OpenGL::init(1280, 720);

    camera.window = &window;
    player.transform.position = glm::vec3(0, 0, 1);

    world.init();

    world.generate(0);

    blockRegistry.add(BlockEntry {0, nullptr}); // air

    Texture* stone = Texture::loadFromImage(PNG::loadFromFile("assets/minecraft/textures/blocks/stone.png"));
    blockRegistry.add(BlockEntry {1, stone});

    Texture* grass = Texture::loadFromImage(PNG::loadFromFile("assets/minecraft/textures/blocks/grass_top.png"));
    blockRegistry.add(BlockEntry {2, grass});

    Texture* dirt = Texture::loadFromImage(PNG::loadFromFile("assets/minecraft/textures/blocks/dirt.png"));
    blockRegistry.add(BlockEntry {3, dirt});

    // init IMGUI

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
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

    running = running && !window.shouldClose();

    OpenGL::clear(0.55f, 0.9f, 1.0f);

    player.update();

    world.render(camera.getProjView(player.transform));

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("World");

    int seed = 0;
    ImGui::InputInt("World seed", &seed);
    if (ImGui::Button("Random seed")) {
        seed = randomInt(0, 10000000);
    }

    if (ImGui::Button("Regenerate world")) {
        world.generate(seed);
    }

    ImGui::End();

    ImGui::Begin("Render");

    if (ImGui::Checkbox("Wireframe mode", &OpenGL::wireframe)) OpenGL::updateWireframe();
    
    ImGui::Text("%01f ms | %d FPS", deltaTime * 1000, (int)(1 / deltaTime));

    ImGui::Text("%d draw calls", drawCalls);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    drawCalls = 0;

    window.update();
}

void Minecraft::run() {
    while (running) {
        update();
    }
}

void Minecraft::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    input.destroy();
    window.destroy();
}