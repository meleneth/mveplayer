#include <sstream>

#include <catch2/catch_test_macros.hpp>
#include <log/log.hpp>
#include <mve/opcode/opcode_video_data.hpp>
#include <mve/opcode/movie_player.hpp>
#include <mve/hex_dump.hpp>

#include "bytes.hpp"

TEST_CASE("OpcodeVideoData#process_encoding_00 copies current_frame to next_frame for block")
{
  using namespace mve;

  std::vector<uint8_t> raw_payload = { };
  std::span<const uint8_t> payload(raw_payload);

  mve::MoviePlayer movie_player;
  mve::OpcodeVideoData opcode(0x11, 0, payload);
  
  movie_player.allocate_video_buffer(1, 1);

  auto v = vhex(R"(
    00 00 00  01 01 01  02 02 02  03 03 03  04 04 04  05 05 05  06 06 06  07 07 07
    08 08 08  09 09 09  0a 0a 0a  0b 0b 0b  0c 0c 0c  0d 0d 0d  0e 0e 0e  0f 0f 0f
    10 10 10  11 11 11  12 12 12  13 13 13  14 14 14  15 15 15  16 16 16  17 17 17
    18 18 18  19 19 19  1a 1a 1a  1b 1b 1b  1c 1c 1c  1d 1d 1d  1e 1e 1e  1f 1f 1f
    20 20 20  21 21 21  22 22 22  23 23 23  24 24 24  25 25 25  26 26 26  27 27 27
    28 28 28  29 29 29  2a 2a 2a  2b 2b 2b  2c 2c 2c  2d 2d 2d  2e 2e 2e  2f 2f 2f
    30 30 30  31 31 31  32 32 32  33 33 33  34 34 34  35 35 35  36 36 36  37 37 37
    38 38 38  39 39 39  3a 3a 3a  3b 3b 3b  3c 3c 3c  3d 3d 3d  3e 3e 3e  3f 3f 3f
  )");

  std::copy(v.begin(), v.end(), movie_player.current_frame->raw_data.begin());

  opcode.process_encoding_00(0, 0, movie_player);

  REQUIRE_THAT(movie_player.new_frame->raw_data, BytesEqualWindow(v));

}
