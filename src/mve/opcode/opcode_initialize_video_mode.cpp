#include<log/log.hpp>
#include<mve/hex_dump.hpp>
#include<mve/opcode/opcode.hpp>
#include<mve/opcode/movie_player.hpp>
#include<mve/opcode/opcode_initialize_video_mode.hpp>

namespace mve {


OpcodeInitializeVideoMode::OpcodeInitializeVideoMode(uint8_t type, uint8_t version, const std::span<const uint8_t> payload)
    : Opcode(type, version, payload.size() > 6 ? payload.subspan(6) : std::span<const uint8_t>{})
{
    if (payload.size() != 6) {
        spdlog::error("    payload for {} was {} bytes! [{}]", name(), payload.size(), hex_dump(payload));
        throw std::runtime_error("OpcodeInitializeVideoMode: payload must be exactly 6 bytes");
    }

    x_resolution = payload[0] | (payload[1] << 8);
    y_resolution = payload[2] | (payload[3] << 8);
    flags        = payload[4] | (payload[5] << 8);
}

std::string OpcodeInitializeVideoMode::name() const {
    return "OpcodeInitializeVideoMode";
}

void OpcodeInitializeVideoMode::process(MoviePlayer &movie_player) const {
  spdlog::info("    InitializeVideoMode(x={}, y={}, flags={})", x_resolution, y_resolution, flags);
  (void)movie_player;
}


};
