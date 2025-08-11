#include<log/log.hpp>
#include<mve/hex_dump.hpp>
#include<mve/opcode/movie_player.hpp>
#include<mve/opcode/opcode_set_palette.hpp>

namespace mve {

OpcodeSetPalette::OpcodeSetPalette(uint8_t type, uint8_t version, const std::span<const uint8_t> payload)
    : Opcode(type, version, payload.size() > 4 ? payload.subspan(4) : std::span<const uint8_t>{})
{
  if (payload.size() < 4) {
    spdlog::error("    payload not long enough - {} bytes", payload.size());
    throw std::runtime_error("OpcodeSetPalette: not long enough");
  }

  pal_start = payload[0] | (payload[1] << 8);
  pal_count = payload[2] | (payload[3] << 8);

  if ((payload.size() - 4) != (pal_count * 3)) {
    spdlog::error("    payload for {} was {} bytes, expected {}! [{}]",
      name(),
      payload.size() - 4,
      (pal_count * 3) - 4,
      hex_dump(payload)
    );
    throw std::runtime_error("OpcodeSetPalette: payload must be exactly 3 * pal_count bytes");
  }
}

std::string OpcodeSetPalette::name() const
{
  return "OpcodeSetPalette";
}

void OpcodeSetPalette::process(MoviePlayer &movie_player) const
{
  spdlog::info("    OpcodeSetPalette(pal_start={}, pal_count={}, data.size={}) | {}", pal_start, pal_count, data().size(), hex_dump(data()));
  const std::size_t count = payload_.size() / 3;
  movie_player.ensure_palette_size(pal_start + pal_count);

  for (std::size_t i = 0; i < count; ++i) {
    std::size_t offset = i * 3;

    movie_player.set_palette_from_6bit(pal_start + i,
      payload_[offset],
      payload_[offset + 1],
      payload_[offset + 2]
    );
  }
}

};
