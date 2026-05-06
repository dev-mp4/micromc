#ifndef MICROMC_FILE_HPP
#define MICROMC_FILE_HPP

#include <stdexcept>
#include <string>
#include <fstream>

inline std::string readFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("File " + path + " not found!");
    }

    std::string contents(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    return contents;
}

#endif // MICROMC_FILE_HPP