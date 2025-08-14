#include <sstream>

#include <catch2/catch_test_macros.hpp>
#include <log/log.hpp>
#include <mve/opcode/opcode_video_data.hpp>
#include <mve/opcode/movie_player.hpp>
#include <mve/hex_dump.hpp>

#include "bytes.hpp"

TEST_CASE("OpcodeVideoData#process_encoding_08 increments based on first 2 bytes")
{
  using namespace mve;

  auto d = vhex(R"(
    00 22 f9 9f 11 33 cc 33 44 55 aa 55 66 77 01 ef
  )");
  std::span<const uint8_t> payload(d);

  auto expected = vhex(R"(
    22 22 22  22 22 22  22 22 22  22 22 22   33 33 33  33 33 33  11 11 11  11 11 11
    22 22 22  00 00 00  00 00 00  22 22 22   33 33 33  33 33 33  11 11 11  11 11 11
    22 22 22  00 00 00  00 00 00  22 22 22   11 11 11  11 11 11  33 33 33  33 33 33
    22 22 22  22 22 22  22 22 22  22 22 22   11 11 11  11 11 11  33 33 33  33 33 33

    55 55 55  44 44 44  55 55 55  44 44 44   66 66 66  66 66 66  66 66 66  66 66 66
    55 55 55  44 44 44  55 55 55  44 44 44   66 66 66  66 66 66  66 66 66  77 77 77
    44 44 44  55 55 55  44 44 44  55 55 55   77 77 77  77 77 77  77 77 77  66 66 66
    44 44 44  55 55 55  44 44 44  55 55 55   77 77 77  77 77 77  77 77 77  77 77 77

  )");

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, payload);
  
  movie_player.allocate_video_buffer(1, 1);
  movie_player.ensure_palette_size(120);
  for (uint8_t i = 0; i < 120; ++i) {
      movie_player.palette[i] = MPRGB8{ i, i, i };
  }

  opcode.process_encoding_08(0, 0, movie_player);

  REQUIRE_THAT(movie_player.new_frame->raw_data, BytesEqualWindow(expected));
  REQUIRE(opcode.stream_index == 16);
}
/*
TEST_CASE("OpcodeVideoData#process_encoding_08 horizontally split block")
{
  using namespace mve;

  auto d = vhex(R"(
    22 00 01 37 f7 31 11 66 8c e6 73 31
  )");

  std::span<const uint8_t> payload(d);

  auto expected = vhex(R"(
    22 22 22  22 22 22  22 22 22  22 22 22  66 66 66  11 11 11  11 11 11  11 11 11
    22 22 22  22 22 22  22 22 22  00 00 00  66 66 66  66 66 66  11 11 11  11 11 11
    22 22 22  22 22 22  00 00 00  00 00 00  66 66 66  66 66 66  66 66 66  11 11 11
    22 22 22  00 00 00  00 00 00  00 00 00  11 11 11  66 66 66  66 66 66  11 11 11
    00 00 00  00 00 00  00 00 00  00 00 00  11 11 11  66 66 66  66 66 66  66 66 66
    22 22 22  00 00 00  00 00 00  00 00 00  11 11 11  11 11 11  66 66 66  66 66 66
    22 22 22  22 22 22  00 00 00  00 00 00  11 11 11  11 11 11  66 66 66  66 66 66
  )");

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, payload);
  
  movie_player.allocate_video_buffer(1, 1);
  movie_player.ensure_palette_size(120);
  for (uint8_t i = 0; i < 120; ++i) {
      movie_player.palette[i] = MPRGB8{ i, i, i };
  }

  opcode.process_encoding_08(0, 0, movie_player);

  REQUIRE_THAT(movie_player.new_frame->raw_data, BytesEqualWindow(expected));
  REQUIRE(opcode.stream_index == 10);
}

TEST_CASE("OpcodeVideoData#process_encoding_08 vertically split block")
{
  using namespace mve;

  auto d = vhex(R"(
    22 00 cc 66 33 19 66 11 18 24 42 81
  )");

  std::span<const uint8_t> payload(d);

  auto expected = vhex(R"(
    00 00 00  00 00 00  22 22 22  22 22 22   00 00 00  00 00 00  22 22 22  22 22 22
    22 22 22  00 00 00  00 00 00  22 22 22   22 22 22  00 00 00  00 00 00  22 22 22
    22 22 22  22 22 22  00 00 00  00 00 00   22 22 22  22 22 22  00 00 00  00 00 00
    22 22 22  22 22 22  22 22 22  00 00 00   00 00 00  22 22 22  22 22 22  00 00 00

    66 66 66  66 66 66  66 66 66  11 11 11   11 11 11  66 66 66  66 66 66  66 66 66
    66 66 66  66 66 66  11 11 11  66 66 66   66 66 66  11 11 11  66 66 66  66 66 66
    66 66 66  11 11 11  66 66 66  66 66 66   66 66 66  66 66 66  11 11 11  66 66 66
    11 11 11  66 66 66  66 66 66  66 66 66   66 66 66  66 66 66  66 66 66  11 11 11
  )");

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, payload);
  
  movie_player.allocate_video_buffer(1, 1);
  movie_player.ensure_palette_size(120);
  for (uint8_t i = 0; i < 120; ++i) {
      movie_player.palette[i] = MPRGB8{ i, i, i };
  }

  opcode.process_encoding_08(0, 0, movie_player);

  REQUIRE_THAT(movie_player.new_frame->raw_data, BytesEqualWindow(expected));
  REQUIRE(opcode.stream_index == 10);
}
*/
