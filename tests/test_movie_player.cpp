#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include "mve/opcode/movie_player.hpp"
#include <log/log.hpp>

TEST_CASE("MoviePlayer set_palette_data")
{
  mve::MoviePlayer movie_player;
  
  movie_player.set_palette(1, 48, 88, 128);

  REQUIRE(movie_player.palette[1].r == 48);
  REQUIRE(movie_player.palette[1].g == 88);
  REQUIRE(movie_player.palette[1].b == 128);
}

TEST_CASE("MoviePlayer#allocate_video_buffer()")
{
  mve::MoviePlayer movie_player;
  movie_player.allocate_video_buffer(1, 1);

  REQUIRE(movie_player.current_frame->raw_data.size() == 192);
  REQUIRE(movie_player.new_frame->raw_data.size() == 192);
}
