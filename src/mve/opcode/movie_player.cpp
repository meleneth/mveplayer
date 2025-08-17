#include <mve/opcode/movie_player.hpp>

#include <memory>    // for std::unique_ptr, std::make_unique
#include <vector>    // for std::vector<uint8_t>
#include <cstdint>   // for uint8_t

namespace mve {

MoviePlayer::MoviePlayer()
{
  decoding_map = nullptr;
  window = nullptr;
  renderer=nullptr;
  texture=nullptr;
}

MoviePlayer::~MoviePlayer()
{
  if(window) {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
  }
}

void MoviePlayer::swap_buffers() noexcept
{
  std::swap(current_frame, new_frame);
}

void MoviePlayer::render_current_to_screen()
{
  SDL_Rect rect = {0, 0, 640, 320};

  SDL_UpdateTexture(texture, &rect, current_frame->raw_data.data(), pitch);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, nullptr, nullptr);
  SDL_RenderPresent(renderer);
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

void MoviePlayer::open_window(int width, int height) {
  window = SDL_CreateWindow(
    "SDL2 Render Vector<uint8_t>",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    width, height,
    SDL_WINDOW_SHOWN
  );

  renderer = SDL_CreateRenderer(
    window, -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );
  
  texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_RGB24,
    SDL_TEXTUREACCESS_STREAMING,
    640, 320
  );

}

}
