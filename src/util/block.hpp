#ifndef MICROMC_BLOCK_DEF_HPP
#define MICROMC_BLOCK_DEF_HPP

#include <array>

constexpr std::array<float, 30> BLOCK_FRONT = {
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f,

    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
};

constexpr std::array<float, 30> BLOCK_BACK = {
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
};

constexpr std::array<float, 30> BLOCK_LEFT = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
};

constexpr std::array<float, 30> BLOCK_RIGHT = {
     0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f,

     0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
};

constexpr std::array<float, 30> BLOCK_TOP = {
    // Top (+Y)
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
};

constexpr std::array<float, 30> BLOCK_BOTTOM = {
    // Bottom (-Y)
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
};

#endif // MICROMC_BLOCK_DEF_HPP