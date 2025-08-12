#include <algorithm>
#include<mve/opcode/opcode_video_data.hpp>
#include<mve/opcode/movie_player.hpp>

namespace mve {

OpcodeVideoData::OpcodeVideoData(uint8_t type, uint8_t version, const std::span<const uint8_t> payload)
    : Opcode(type, version, payload)
{
}

std::string OpcodeVideoData::name() const
{
    return "OpcodeVideoData";
}

void OpcodeVideoData::process(MoviePlayer &movie_player) const
{
  (void)movie_player;
}

void OpcodeVideoData::process_encoding_00(int x, int y, MoviePlayer &movie_player)
{
  for(int i = 0; i < 8; i++) {
    auto src = std::span<uint8_t>(movie_player.current_frame->raw_data).subspan(x * 3 + ((i + y) * movie_player.pitch), 24);
    auto dst = std::span<uint8_t>(    movie_player.new_frame->raw_data).subspan(x * 3 + ((i + y) * movie_player.pitch), 24);
    std::copy_n(src.data(), src.size(), dst.data());
  }
}

void OpcodeVideoData::process_encoding_01(int x, int y, MoviePlayer &movie_player)
{
  (void)movie_player;
  (void)x;
  (void)y;
}

};
