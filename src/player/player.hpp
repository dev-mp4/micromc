#ifndef MICROMC_PLAYER_HPP
#define MICROMC_PLAYER_HPP

#include "object/entitytransform.hpp"
#include <player/camera.hpp>

class Player {
public:
    Player();
    ~Player();

    EntityTransform transform;

    float sensitivity = 0.5f;
    float speed = 6.0f;

    bool mouseLocked = false;
    
    void update();

private:
    float rotationX, rotationY = 0.0f; 
};

#endif // MICROMC_PLAYER_HPP