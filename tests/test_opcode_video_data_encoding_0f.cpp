#include <sstream>

#include <catch2/catch_test_macros.hpp>
#include <log/log.hpp>
#include <mve/opcode/opcode_video_data.hpp>
#include <mve/opcode/movie_player.hpp>
#include <mve/hex_dump.hpp>

#include "bytes.hpp"

TEST_CASE("OpcodeVideoData#process_encoding_0f dither")
{
  using namespace mve;

  auto d = vhex(R"(
    03 04
  )");

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, d);
  
  movie_player.allocate_video_buffer(1, 1);

  auto v = vhex(R"(
    03 03 03  04 04 04  03 03 03  04 04 04  03 03 03  04 04 04  03 03 03  04 04 04
    04 04 04  03 03 03  04 04 04  03 03 03  04 04 04  03 03 03  04 04 04  03 03 03
    03 03 03  04 04 04  03 03 03  04 04 04  03 03 03  04 04 04  03 03 03  04 04 04
    04 04 04  03 03 03  04 04 04  03 03 03  04 04 04  03 03 03  04 04 04  03 03 03
    03 03 03  04 04 04  03 03 03  04 04 04  03 03 03  04 04 04  03 03 03  04 04 04
    04 04 04  03 03 03  04 04 04  03 03 03  04 04 04  03 03 03  04 04 04  03 03 03
    03 03 03  04 04 04  03 03 03  04 04 04  03 03 03  04 04 04  03 03 03  04 04 04
    04 04 04  03 03 03  04 04 04  03 03 03  04 04 04  03 03 03  04 04 04  03 03 03
  )");


  movie_player.ensure_palette_size(6);
  for (uint8_t i = 0; i < 6; ++i) {
      movie_player.palette[i] = MPRGB8{ i, i, i };
  }

  opcode.process_encoding_0f(0, 0, movie_player);

  REQUIRE_THAT(movie_player.new_frame->raw_data, BytesEqualWindow(v));
  REQUIRE(opcode.stream_index == 2);
}
