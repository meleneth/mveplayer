#include <sstream>

#include <catch2/catch_test_macros.hpp>
#include <log/log.hpp>
#include <mve/opcode/opcode_video_data.hpp>
#include <mve/opcode/movie_player.hpp>
#include <mve/hex_dump.hpp>

#include "bytes.hpp"

TEST_CASE("OpcodeVideoData#process_encoding_0a increments ")
{
  using namespace mve;

  auto d = vhex(R"(
   00 11 22 33  1c 1c 1c 1c
   22 33 44 55  1c 1c 1c 1c
   01 02 03 04  1c 1c 1c 1c
   02 03 04 05  1c 1c 1c 1c
  )");

  std::span<const uint8_t> payload(d);

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, payload);
  
  movie_player.allocate_video_buffer(1, 1);

  opcode.process_encoding_0a(0, 0, movie_player);

  REQUIRE(opcode.stream_index == 32);
}

TEST_CASE("OpcodeVideoData#process_encoding_0a increments lr")
{
  using namespace mve;

  auto d = vhex(R"(
   11 00 22 33  1c 1c 1c 1c  1c 1c 1c 1c
   00 11 22 33  1c 1c 1c 1c  1c 1c 1c 1c
  )");

  std::span<const uint8_t> payload(d);

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, payload);
 
  movie_player.allocate_video_buffer(1, 1);

  opcode.process_encoding_0a(0, 0, movie_player);

  REQUIRE(opcode.stream_index == 24);
}

TEST_CASE("OpcodeVideoData#process_encoding_0a increments tb")
{
  using namespace mve;

  auto d = vhex(R"(
   11 00 22 33  1c 1c 1c 1c  1c 1c 1c 1c
   00 11 22 33  1c 1c 1c 1c  1c 1c 1c 1c
  )");

  std::span<const uint8_t> payload(d);

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, payload);
 
  movie_player.allocate_video_buffer(1, 1);

  opcode.process_encoding_0a(0, 0, movie_player);

  REQUIRE(opcode.stream_index == 24);
}
