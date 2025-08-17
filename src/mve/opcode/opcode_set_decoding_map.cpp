#include<log/log.hpp>
#include<mve/opcode/opcode_set_decoding_map.hpp>
#include<mve/opcode/movie_player.hpp>

namespace mve {

std::string OpcodeSetDecodingMap::name() const {
    return "OpcodeSetDecodingMap";
}

void OpcodeSetDecodingMap::process(MoviePlayer &movie_player)
{
  spdlog::info("    SetDecodingMap(payload.size={})", payload_.size());
  movie_player.set_decoding_map(this);
  count_encodings();
}

void OpcodeSetDecodingMap::count_encodings() const
{
  // 16 possible 4-bit values: 0x0..0xF
  std::vector<uint16_t> counts(16, 0);

  for (uint8_t byte : payload_) {
      uint8_t low  = byte & 0x0F;
      uint8_t high = (byte >> 4) & 0x0F;

      counts[low]++;   // low nibble
      counts[high]++;  // high nibble
  }

  spdlog::debug("Encoding counts:");
  for (std::size_t i = 0; i < counts.size(); ++i) {
      spdlog::debug("  {:X}: {}", static_cast<unsigned>(i), counts[i]);
  }
}

};
