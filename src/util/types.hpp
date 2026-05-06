#ifndef MICROMC_TYPES_HPP
#define MICROMC_TYPES_HPP

#include <vector>

struct Image {
    int width;
    int height;
    std::vector<unsigned char> data;
};

#endif // MICROMC_TYPES_HPP