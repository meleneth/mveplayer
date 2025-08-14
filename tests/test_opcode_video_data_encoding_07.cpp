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

  auto d = vhex(R"(
   22 11 f0 81
  )");
  std::span<const uint8_t> payload(d);

  auto expected = vhex(R"(
    22 22 22  22 22 22  22 22 22  22 22 22   22 22 22  22 22 22  22 22 22  22 22 22
    22 22 22  22 22 22  22 22 22  22 22 22   22 22 22  22 22 22  22 22 22  22 22 22
    11 11 11  11 11 11  11 11 11  11 11 11   11 11 11  11 11 11  11 11 11  11 11 11
    11 11 11  11 11 11  11 11 11  11 11 11   11 11 11  11 11 11  11 11 11  11 11 11

    22 22 22  22 22 22  11 11 11  11 11 11   11 11 11  11 11 11  11 11 11  11 11 11
    22 22 22  22 22 22  11 11 11  11 11 11   11 11 11  11 11 11  11 11 11  11 11 11
    11 11 11  11 11 11  11 11 11  11 11 11   11 11 11  11 11 11  22 22 22  22 22 22
    11 11 11  11 11 11  11 11 11  11 11 11   11 11 11  11 11 11  22 22 22  22 22 22
  )");


  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, payload);
  
  movie_player.allocate_video_buffer(1, 1);
  movie_player.ensure_palette_size(40);
  for (uint8_t i = 0; i < 40; ++i) {
      movie_player.palette[i] = MPRGB8{ i, i, i };
  }

  opcode.process_encoding_07(0, 0, movie_player);

  REQUIRE_THAT(movie_player.new_frame->raw_data, BytesEqualWindow(expected));
  REQUIRE(opcode.stream_index == 4);
}

TEST_CASE("OpcodeVideoData#process_encoding_07 renders based on bit pattern")
{
  using namespace mve;

  auto d = vhex(R"(
    11 22
    ff 81 81 81 81 81 81 ff
  )");

  std::span<const uint8_t> payload(d);

  auto expected = vhex(R"(
    22 22 22  22 22 22  22 22 22  22 22 22   22 22 22  22 22 22  22 22 22  22 22 22
    22 22 22  11 11 11  11 11 11  11 11 11   11 11 11  11 11 11  11 11 11  22 22 22
    22 22 22  11 11 11  11 11 11  11 11 11   11 11 11  11 11 11  11 11 11  22 22 22
    22 22 22  11 11 11  11 11 11  11 11 11   11 11 11  11 11 11  11 11 11  22 22 22

    22 22 22  11 11 11  11 11 11  11 11 11   11 11 11  11 11 11  11 11 11  22 22 22
    22 22 22  11 11 11  11 11 11  11 11 11   11 11 11  11 11 11  11 11 11  22 22 22
    22 22 22  11 11 11  11 11 11  11 11 11   11 11 11  11 11 11  11 11 11  22 22 22
    22 22 22  22 22 22  22 22 22  22 22 22   22 22 22  22 22 22  22 22 22  22 22 22
  )");

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, payload);
  
  movie_player.allocate_video_buffer(1, 1);
  movie_player.ensure_palette_size(40);
  for (uint8_t i = 0; i < 40; ++i) {
      movie_player.palette[i] = MPRGB8{ i, i, i };
  }

  opcode.process_encoding_07(0, 0, movie_player);

  REQUIRE_THAT(movie_player.new_frame->raw_data, BytesEqualWindow(expected));
  REQUIRE(opcode.stream_index == 10);
}
