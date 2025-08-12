#include <sstream>

#include <catch2/catch_test_macros.hpp>
#include <log/log.hpp>
#include <mve/opcode/opcode_video_data.hpp>
#include <mve/opcode/movie_player.hpp>
#include <mve/hex_dump.hpp>

#include "bytes.hpp"

TEST_CASE("OpcodeVideoData#process_encoding_0d raw video bytes 4x4")
{
  using namespace mve;

  auto d = vhex(R"(
    00 01 02 03
  )");

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, d);
  
  movie_player.allocate_video_buffer(1, 1);

  auto v = vhex(R"(
    00 00 00  00 00 00  00 00 00  00 00 00  01 01 01  01 01 01  01 01 01  01 01 01  
    00 00 00  00 00 00  00 00 00  00 00 00  01 01 01  01 01 01  01 01 01  01 01 01  
    00 00 00  00 00 00  00 00 00  00 00 00  01 01 01  01 01 01  01 01 01  01 01 01  
    00 00 00  00 00 00  00 00 00  00 00 00  01 01 01  01 01 01  01 01 01  01 01 01  
    02 02 02  02 02 02  02 02 02  02 02 02  03 03 03  03 03 03  03 03 03  03 03 03  
    02 02 02  02 02 02  02 02 02  02 02 02  03 03 03  03 03 03  03 03 03  03 03 03  
    02 02 02  02 02 02  02 02 02  02 02 02  03 03 03  03 03 03  03 03 03  03 03 03  
    02 02 02  02 02 02  02 02 02  02 02 02  03 03 03  03 03 03  03 03 03  03 03 03  
  )");


  movie_player.ensure_palette_size(16);
  for (uint8_t i = 0; i < 16; ++i) {
      movie_player.palette[i] = MPRGB8{ i, i, i };
  }

  opcode.process_encoding_0d(0, 0, movie_player);

  REQUIRE_THAT(movie_player.new_frame->raw_data, BytesEqualWindow(v));
  REQUIRE(opcode.stream_index == 4);
}
