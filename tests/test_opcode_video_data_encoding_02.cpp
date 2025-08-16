#include <sstream>

#include <catch2/catch_test_macros.hpp>
#include <log/log.hpp>
#include <mve/opcode/opcode_video_data.hpp>
#include <mve/opcode/movie_player.hpp>
#include <mve/hex_dump.hpp>

#include "bytes.hpp"

TEST_CASE("OpcodeVideoData#process_encoding_02 increments ")
{
  using namespace mve;

  std::vector<uint8_t> raw_payload = { };
  std::span<const uint8_t> payload(raw_payload);

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, payload);
  
  movie_player.allocate_video_buffer(1, 1);

  opcode.process_encoding_02(0, 0, movie_player);

  REQUIRE(opcode.stream_index == 1);
}
