#pragma once
#include <memory>
#include <mve/chunk.hpp>

namespace mve {

class Opcode {
public:
    virtual ~Opcode() = default;
    virtual void execute() = 0;
};

std::unique_ptr<Opcode> decode_opcode(const Chunk& chunk);

} // namespace mve
