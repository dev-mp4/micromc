#ifndef MICROMC_INPUT_HPP
#define MICROMC_INPUT_HPP

#include <window.hpp>
#include <glm/glm.hpp>
#include <bitset>

class Input {
public:
    Input();
    ~Input();

    void init(Window& window);
    void destroy();
    void poll();

    bool getKey(int key);
    bool getKeyDown(int key);
    bool getKeyUp(int key);

    bool getMouseButton(int button);
    bool getMouseButtonDown(int button);
    bool getMouseButtonUp(int button);

    glm::vec2 getMousePos();
    glm::vec2 getMouseDelta();

    void setKeyState(int key, bool state);
    void setMousePos(glm::vec2 pos);

private:
    std::bitset<1024> currentFrame;
    std::bitset<1024> previvousFrame;

    std::bitset<8> mouseCurrentFrame;
    std::bitset<8> mousePrevivousFrame;

    glm::vec2 mousePos;
    glm::vec2 mouseDelta;
};

#endif // MICROMC_INPUT_HPP