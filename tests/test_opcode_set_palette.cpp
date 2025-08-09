#include <sstream>

#include <catch2/catch_test_macros.hpp>
#include <log/log.hpp>
#include <mve/opcode/opcode_set_palette.hpp>
#include <mve/opcode/movie_player.hpp>
#include <mve/hex_dump.hpp>

TEST_CASE("OpcodeSetPalette parses pal_start and pal_count correctly from raw payload")
{
  using namespace mve;

  mve::MoviePlayer movie_player;

  std::vector<uint8_t> raw_payload = {
    0x01, 0x00,  // pal_start = 1
    0x01, 0x00,  // pal_count = 1
    0x8c, 0x05, 0x02
  };

  std::span<const uint8_t> payload(raw_payload);

  OpcodeSetPalette opcode(0x0c, 12, payload);

  REQUIRE(opcode.type() == 12);
  REQUIRE(opcode.pal_start == 1);
  REQUIRE(opcode.pal_count == 1);
  REQUIRE(opcode.data().size() == 3);

  opcode.process(movie_player);

  REQUIRE(movie_player.palette()[1].r == 48);
  REQUIRE(movie_player.palette()[1].g == 89);
  REQUIRE(movie_player.palette()[1].b == 130);
}
