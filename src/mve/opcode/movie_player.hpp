#pragma once

#include<SDL.h>

#include <cstdint>
#include <vector>
#include <memory>

#include <mve/opcode/buffer.hpp>
#include <mve/opcode/scanner_b.hpp>

namespace mve {

#pragma pack(push, 1)
struct MPRGB8 {
  uint8_t r{0}, g{0}, b{0};
};

#pragma pack(pop)

struct ExpandedPalette {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

class OpcodeSetDecodingMap;
class MoviePlayer {
public:
  MoviePlayer();
  ~MoviePlayer();

  void swap_buffers() noexcept;

  void set_decoding_map(const OpcodeSetDecodingMap *decoding_map);

  const OpcodeSetDecodingMap *decoding_map;

  void set_palette(std::size_t index, uint8_t r, uint8_t g, uint8_t b);
  void set_palette_from_6bit(std::size_t index, uint8_t r6, uint8_t g6, uint8_t b6);
  void ensure_palette_size(std::size_t size);
  void render_current_to_screen();
  uint8_t expand6to8(uint8_t v6) noexcept;

  void allocate_video_buffer(std::size_t x_blocks, std::size_t y_blocks);

  void open_window(int x, int y);

  std::unique_ptr<Buffer> current_frame;
  std::unique_ptr<Buffer> new_frame;
  std::vector<MPRGB8> palette;

  uint16_t x_pixels;
  uint16_t y_pixels;
  uint16_t x_blocks;
  uint16_t y_blocks;
  uint16_t pitch;
  int chunk_no;
  ScannerB scanner_b;
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture *texture;
};

}
