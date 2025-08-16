#pragma once
#include <cstdint>
#include <vector>
#include <memory>

namespace mve {

class Buffer {
public:
    explicit Buffer(std::size_t num_bytes)
      : raw_data(num_bytes, 0) {};
    std::vector<uint8_t> raw_data;
};

}
