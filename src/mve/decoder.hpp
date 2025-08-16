#pragma once
#include <istream>
#include <vector>
#include <memory>

#include <mve/chunk.hpp>
#include <mve/opcode/opcode.hpp>

namespace mve {

class Decoder {
public:
    explicit Decoder(std::istream& input);
    bool valid() const;
    std::unique_ptr<Chunk> next_chunk();
private:
    std::istream& input_;
    bool valid_ = false;
    bool parse_header();
};

} // namespace mve
