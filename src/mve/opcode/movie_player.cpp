#include <mve/opcode/movie_player.hpp>

namespace mve {

MoviePlayer::MoviePlayer()
{
  decoding_map = nullptr;
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

void MoviePlayer::set_decoding_map(const OpcodeSetDecodingMap *decoding_map)
{
  this->decoding_map = decoding_map;
}

}
