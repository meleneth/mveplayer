#include<log/log.hpp>
#include<mve/opcode/opcode_set_decoding_map.hpp>
#include<mve/opcode/movie_player.hpp>

namespace mve {

std::string OpcodeSetDecodingMap::name() const {
    return "OpcodeSetDecodingMap";
}

void OpcodeSetDecodingMap::process(MoviePlayer &movie_player) const
{
  spdlog::info("    SetDecodingMap(payload.size={})", payload_.size());
  movie_player.set_decoding_map(this);
}

};
