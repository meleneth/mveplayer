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

uint8_t MoviePlayer::expand6to8(uint8_t v6) noexcept
{
  // nicer than (v6 << 2): fills low bits for a smoother ramp
  return static_cast<uint8_t>((v6 << 2) | (v6 >> 4));
}

void MoviePlayer::ensure_palette_size(std::size_t size)
{
  if (palette_.size() < size) {
    palette_.resize(size);
  }
}

void MoviePlayer::set_palette(std::size_t index, uint8_t r, uint8_t g, uint8_t b)
{
  if (index >= palette_.size()) {
    palette_.resize(index + 1);
  }
  palette_[index] = MPRGB8{r, g, b};
}

void MoviePlayer::set_palette_from_18bit(std::size_t index, uint8_t r6, uint8_t g6, uint8_t b6)
{
  set_palette(index, expand6to8(r6), expand6to8(g6), expand6to8(b6));
}

}
