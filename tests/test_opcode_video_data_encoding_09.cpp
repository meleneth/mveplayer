#include <sstream>

#include <catch2/catch_test_macros.hpp>
#include <log/log.hpp>
#include <mve/opcode/opcode_video_data.hpp>
#include <mve/opcode/movie_player.hpp>
#include <mve/hex_dump.hpp>

#include "bytes.hpp"

TEST_CASE("OpcodeVideoData#process_encoding_09 1x1 2 bit patterns ")
{
  using namespace mve;
//Now, if P0 <= P1 AND P2 <= P3, we get 16 bytes of pattern, 
//each 2 bits representing a 1x1 pixel (00=P0, 01=P1, 10=P2, 11=P3). 
//The ordering is again left to right and top to bottom. 
//The most significant bits represent the left side at the top, and so on.

  auto d = vhex(R"(
    00 11 22 33

    1B E4
    1B E4
    E4 1B
    E4 1B

    87 D2
    87 D2
    D2 87
    D2 87
  )");
  std::span<const uint8_t> payload(d);

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, payload);

  auto expected = vhex(R"(
    00 00 00  11 11 11  22 22 22  33 33 33   33 33 33  22 22 22  11 11 11  00 00 00
    00 00 00  11 11 11  22 22 22  33 33 33   33 33 33  22 22 22  11 11 11  00 00 00
    33 33 33  22 22 22  11 11 11  00 00 00   00 00 00  11 11 11  22 22 22  33 33 33  
    33 33 33  22 22 22  11 11 11  00 00 00   00 00 00  11 11 11  22 22 22  33 33 33  

    22 22 22  00 00 00  11 11 11  33 33 33   33 33 33  11 11 11  00 00 00  22 22 22
    22 22 22  00 00 00  11 11 11  33 33 33   33 33 33  11 11 11  00 00 00  22 22 22
    33 33 33  11 11 11  00 00 00  22 22 22   22 22 22  00 00 00  11 11 11  33 33 33 
    33 33 33  11 11 11  00 00 00  22 22 22   22 22 22  00 00 00  11 11 11  33 33 33 
  )");

  
  movie_player.allocate_video_buffer(1, 1);
  movie_player.ensure_palette_size(120);
  for (uint8_t i = 0; i < 120; ++i) {
      movie_player.palette[i] = MPRGB8{ i, i, i };
  }

  opcode.process_encoding_09(0, 0, movie_player);

  REQUIRE_THAT(movie_player.new_frame->raw_data, BytesEqualWindow(expected));
  REQUIRE(opcode.stream_index == 20);
}

TEST_CASE("OpcodeVideoData#process_encoding_09 2x2 2 bit patterns ")
{
  using namespace mve;
  // If P0 <= P1 AND P2 > P3, we get 4 bytes of pattern,
  // each 2 bits representing a 2x2 pixel. 
  // Ordering is left to right and top to bottom.

  auto d = vhex(R"(
    00 11 33 22  1B E4 1B E4
  )");
  std::span<const uint8_t> payload(d);

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, payload);

  auto expected = vhex(R"(
    00 00 00  00 00 00  11 11 11  11 11 11   33 33 33  33 33 33  22 22 22  22 22 22
    00 00 00  00 00 00  11 11 11  11 11 11   33 33 33  33 33 33  22 22 22  22 22 22
    22 22 22  22 22 22  33 33 33  33 33 33   11 11 11  11 11 11  00 00 00  00 00 00
    22 22 22  22 22 22  33 33 33  33 33 33   11 11 11  11 11 11  00 00 00  00 00 00

    00 00 00  00 00 00  11 11 11  11 11 11   33 33 33  33 33 33  22 22 22  22 22 22
    00 00 00  00 00 00  11 11 11  11 11 11   33 33 33  33 33 33  22 22 22  22 22 22
    22 22 22  22 22 22  33 33 33  33 33 33   11 11 11  11 11 11  00 00 00  00 00 00
    22 22 22  22 22 22  33 33 33  33 33 33   11 11 11  11 11 11  00 00 00  00 00 00
  )");

  
  movie_player.allocate_video_buffer(1, 1);
  movie_player.ensure_palette_size(120);
  for (uint8_t i = 0; i < 120; ++i) {
      movie_player.palette[i] = MPRGB8{ i, i, i };
  }

  opcode.process_encoding_09(0, 0, movie_player);

  REQUIRE_THAT(movie_player.new_frame->raw_data, BytesEqualWindow(expected));
  REQUIRE(opcode.stream_index == 8);
}

TEST_CASE("OpcodeVideoData#process_encoding_09 2x1 2 bit patterns ")
{
  using namespace mve;
  //if P0 > P1 AND P2 <= P3, we get 8 bytes of pattern, 
  //each 2 bits representing a 2x1 pixel (i.e. 2 pixels wide, and 1 high).


  auto d = vhex(R"(
    11 00 22 33  1B E4 1B E4  D2 87 D2 87
  )");
  std::span<const uint8_t> payload(d);

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, payload);

  auto expected = vhex(R"(
  )");

  
  movie_player.allocate_video_buffer(1, 1);
  movie_player.ensure_palette_size(120);
  for (uint8_t i = 0; i < 120; ++i) {
      movie_player.palette[i] = MPRGB8{ i, i, i };
  }

  opcode.process_encoding_09(0, 0, movie_player);

  REQUIRE_THAT(movie_player.new_frame->raw_data, BytesEqualWindow(expected));
  REQUIRE(opcode.stream_index == 0);
}

/*
TEST_CASE("OpcodeVideoData#process_encoding_09 1x2 2 bit patterns ")
{
  using namespace mve;
  //if P0 > P1 AND P2 > P3, we get 8 bytes of pattern,
  //each 2 bits representing a 1x2 pixel (i.e. 1 pixel wide, and 2 high).

  auto d = vhex(R"(
    11 00 33 22  1B E4 E4 1B  D2 87 87 D2
  )");
  std::span<const uint8_t> payload(d);

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, payload);

  auto expected = vhex(R"(
  )");

  
  movie_player.allocate_video_buffer(1, 1);
  movie_player.ensure_palette_size(120);
  for (uint8_t i = 0; i < 120; ++i) {
      movie_player.palette[i] = MPRGB8{ i, i, i };
  }

  opcode.process_encoding_09(0, 0, movie_player);

  REQUIRE_THAT(movie_player.new_frame->raw_data, BytesEqualWindow(expected));
  REQUIRE(opcode.stream_index == 0);
}
*/
