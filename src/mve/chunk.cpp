#include <istream>

#include <mve/chunk.hpp>

namespace mve {

Chunk Chunk::parse(std::istream& input) {
    Chunk chunk;

    uint8_t opcode_raw;
    input.read(reinterpret_cast<char*>(&opcode_raw), 1);
    chunk.opcode = static_cast<OpcodeType>(opcode_raw);

    input.ignore(1); // skip one byte of padding or unused field

    uint16_t size;
    input.read(reinterpret_cast<char*>(&size), 2);
    chunk.size = size;

    chunk.data.resize(size);
    input.read(reinterpret_cast<char*>(chunk.data.data()), size);

    return chunk;
}

} // namespace mve
