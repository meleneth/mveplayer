#include <sstream>

#include <catch2/catch_test_macros.hpp>
#include <log/log.hpp>
#include <mve/opcode/opcode_video_data.hpp>
#include <mve/opcode/movie_player.hpp>
#include <mve/hex_dump.hpp>

#include "bytes.hpp"

TEST_CASE("OpcodeVideoData#process_encoding_07 increments based on first 2 bytes")
{
  using namespace mve;

  std::vector<uint8_t> raw_payload = { 1, 2, 1, 2, 3, 4, 5, 6, 7, 8};
  std::span<const uint8_t> payload(raw_payload);

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, payload);
  
  movie_player.allocate_video_buffer(1, 1);

  opcode.process_encoding_07(0, 0, movie_player);

  REQUIRE(opcode.stream_index == 10);
}

TEST_CASE("OpcodeVideoData#process_encoding_07 increments based on first 2 bytes - 4 bytes")
{
  using namespace mve;

  std::vector<uint8_t> raw_payload = { 2, 1, 4, 3};
  std::span<const uint8_t> payload(raw_payload);

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, payload);
  
  movie_player.allocate_video_buffer(1, 1);

  opcode.process_encoding_07(0, 0, movie_player);

  REQUIRE(opcode.stream_index == 4);
}
