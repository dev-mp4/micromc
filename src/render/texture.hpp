#ifndef MICROMC_TEXTURE_HPP
#define MICROMC_TEXTURE_HPP

#include <util/types.hpp>

class Texture {
public:
    Texture(unsigned int id);
    ~Texture();

    void bind(int index);
    void destroy();
    static Texture* loadFromImage(Image* image);

private:
    unsigned int id;
};

#endif // MICROMC_TEXTURE_HPP