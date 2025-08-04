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

    struct DecodedChunk {
        uint16_t chunk_type;
        std::vector<std::unique_ptr<Opcode>> opcodes;
    };

    // Returns nullptr when no more data
    std::unique_ptr<DecodedChunk> next_chunk();

private:
    std::istream& input_;
    bool valid_ = false;

    bool parse_header();
};

} // namespace mve
