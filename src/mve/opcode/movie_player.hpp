#pragma once
#include <cstdint>
#include <vector>
#include <memory>

#include <mve/opcode/buffer.hpp>

namespace mve {

class MoviePlayer {
public:
  MoviePlayer();

  void swap_buffers() noexcept;

  Buffer&       current() noexcept;
  const Buffer& current() const noexcept;

  Buffer&       last() noexcept;
  const Buffer& last() const noexcept;

private:
  std::unique_ptr<Buffer> current_frame;
  std::unique_ptr<Buffer> last_frame;
};

}
