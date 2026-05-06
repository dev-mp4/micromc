#include <minecraft.hpp>
#include "window.hpp"
#include <GLFW/glfw3.h>

int main() {
    Minecraft minecraft;

    while (!minecraft.window.shouldClose()) {
        minecraft.update();
    }

    minecraft.destroy();

    return 0;
}