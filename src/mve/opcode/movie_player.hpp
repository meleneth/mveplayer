#pragma once
#include <cstdint>
#include <vector>
#include <memory>

#include <mve/opcode/buffer.hpp>

namespace mve {

#pragma pack(push, 1)
struct MPRGB8 {
  uint8_t r{0}, g{0}, b{0};
};

union MPPackedRGB18LE {
  struct {
    uint8_t b0, b1, b2; // raw 3 bytes
  } raw;

  struct {
    unsigned r;
    unsigned g;
    unsigned b;
  } f;
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

  void swap_buffers() noexcept;

  Buffer&       current() noexcept;
  const Buffer& current() const noexcept;

  Buffer&       last() noexcept;
  const Buffer& last() const noexcept;

  void set_decoding_map(const OpcodeSetDecodingMap *decoding_map);

  const OpcodeSetDecodingMap *decoding_map;

  void set_palette(std::size_t index, uint8_t r, uint8_t g, uint8_t b);
  void set_palette_from_6bit(std::size_t index, uint8_t r6, uint8_t g6, uint8_t b6);
  const std::vector<MPRGB8>& palette() const noexcept { return palette_; }
  void ensure_palette_size(std::size_t size);
  uint8_t expand6to8(uint8_t v6) noexcept;

private:
  std::unique_ptr<Buffer> current_frame;
  std::unique_ptr<Buffer> last_frame;
  std::vector<MPRGB8> palette_;
};

}
