#include "opengl.hpp"
#include <glad/glad.h>
#include <window.hpp>

bool OpenGL::wireframe = false;

bool OpenGL::init(int width, int height) {
    if (!gladLoadGLLoader((GLADloadproc)Window::getGLProcLoader())) {
        return false;
    }

    glViewport(0, 0, width, height);

    return true;
}

void OpenGL::clear(float r, float g, float b) {
    glClearColor(r, g, b, 255);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGL::enableDepth() {
    glEnable(GL_DEPTH_TEST);
}

void OpenGL::disableDepth() {
    glDisable(GL_DEPTH_TEST);
}

void OpenGL::enableCulling() {
    glEnable(GL_CULL_FACE);
}

void OpenGL::disableCulling() {
    glDisable(GL_CULL_FACE);
}

void OpenGL::toggleWireframe() {
    wireframe = !wireframe;
    updateWireframe();
}

void OpenGL::updateWireframe() {
    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}