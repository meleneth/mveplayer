#pragma once
#include <cstdint>
#include <vector>
#include <memory>

namespace mve {

class Buffer {
public:
    Buffer();
private:
    std::vector<uint8_t> raw_data_;
};

}
