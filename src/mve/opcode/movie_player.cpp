#include <mve/opcode/movie_player.hpp>

namespace mve {

MoviePlayer::MoviePlayer()
{

}

void MoviePlayer::swap_buffers() noexcept
{
  std::swap(current_frame, last_frame);
}

Buffer&       MoviePlayer::current() noexcept
{
  return *current_frame;
}

const Buffer& MoviePlayer::current() const noexcept
{
  return *current_frame;
}

Buffer&       MoviePlayer::last() noexcept
{
  return *last_frame;
}

const Buffer& MoviePlayer::last() const noexcept
{
  return *last_frame;
}

}
