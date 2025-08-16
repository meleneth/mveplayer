#include <mve/opcode/movie_player.hpp>

#include <memory>    // for std::unique_ptr, std::make_unique
#include <vector>    // for std::vector<uint8_t>
#include <cstdint>   // for uint8_t

namespace mve {

MoviePlayer::MoviePlayer()
{
  decoding_map = nullptr;
}

void MoviePlayer::swap_buffers() noexcept
{
  std::swap(current_frame, new_frame);
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
  if (palette.size() < size) {
    palette.resize(size);
  }
}

void MoviePlayer::set_palette(std::size_t index, uint8_t r, uint8_t g, uint8_t b)
{
  if (index >= palette.size()) {
    palette.resize(index + 1);
  }
  palette[index] = MPRGB8{r, g, b};
}

void MoviePlayer::set_palette_from_6bit(std::size_t index, uint8_t r6, uint8_t g6, uint8_t b6)
{
  set_palette(index, expand6to8(r6), expand6to8(g6), expand6to8(b6));
}

void MoviePlayer::allocate_video_buffer(std::size_t x_blocks, std::size_t y_blocks)
{
  std::size_t total_pixels = x_blocks * y_blocks;
  pitch = y_blocks * 8 * 3;
  current_frame = std::make_unique<Buffer>(total_pixels * 64 * 3);
  new_frame = std::make_unique<Buffer>(total_pixels * 64 * 3);
}

}
