#include<log/log.hpp>
#include<mve/opcode/opcode_end_of_chunk.hpp>
#include<mve/opcode/movie_player.hpp>

namespace mve {

std::string OpcodeEndOfChunk::name() const
{
    return "OpcodeEndOfChunk";
}

void OpcodeEndOfChunk::process(MoviePlayer &movie_player)
{
  spdlog::info("    OpcodeEndOfChunk()");
  movie_player.set_decoding_map(nullptr);
}

};
