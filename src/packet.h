#pragma once

#include <vector>

namespace unimess {

class Packet {
public:
    std::vector<unsigned char> data;

    Packet() {}
    Packet(std::vector<unsigned char>&& other) {
        data = std::move(other);
    }
};

} // namespace unimess
