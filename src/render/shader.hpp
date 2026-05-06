#ifndef MICROMC_SHADER_HPP
#define MICROMC_SHADER_HPP

#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(unsigned int id);
    ~Shader();

    void use();
    void destroy();
    static Shader* loadFromGLSL(const std::string& vertex, const std::string& fragment);
    void setUniform(const std::string& name, glm::mat4 matrix);

private:
    unsigned int id;
};

#endif //MICROMC_SHADER_HPP