#pragma once
#include <cstdint>

namespace mve {

enum class OpcodeType : uint8_t {
    EndOfStream = 0,
    CreateTimer = 1,
    InitAudioBuffers = 2,
    VideoData = 7,
    Unknown = 255
};

}
