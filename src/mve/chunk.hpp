#pragma once
#include <cstdint>
#include <vector>
#include <memory>

#include <mve/opcode/opcode.hpp>

namespace mve {

class Chunk {
public:
    Chunk(uint16_t type, std::vector<uint8_t>&& data);

    uint16_t type() const;
    size_t size() const;

    void parse_opcodes();  // safe to call multiple times
    const std::vector<std::unique_ptr<Opcode>>& opcodes() const;

private:
    uint16_t type_;
    std::vector<uint8_t> raw_data_;
    std::vector<std::unique_ptr<Opcode>> opcodes_;
};

}
