#pragma once
#include <cstdint>
#include <memory>
#include <vector>

namespace mve {

enum class OpcodeType : uint8_t {
    EndOfStream = 0,
    CreateTimer = 1,
    InitAudioBuffers = 2,
    VideoData = 7,
    Unknown
};

struct Chunk {
    OpcodeType opcode;
    uint16_t size;
    std::vector<uint8_t> data;

    static Chunk parse(std::istream& input);
};

} // namespace mve
