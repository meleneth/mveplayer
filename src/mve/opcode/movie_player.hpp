#pragma once
#include <cstdint>
#include <vector>
#include <memory>

#include <mve/opcode/buffer.hpp>

namespace mve {

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
private:
  std::unique_ptr<Buffer> current_frame;
  std::unique_ptr<Buffer> last_frame;
};

}
