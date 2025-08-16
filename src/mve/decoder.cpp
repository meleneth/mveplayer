#include <array>
#include <stdexcept>
#include <spdlog/spdlog.h>

#include <mve/decoder.hpp>
#include <mve/hex_dump.hpp>

namespace mve {

Decoder::Decoder(std::istream& input)
    : input_(input)
{
    valid_ = parse_header();
}

bool Decoder::valid() const {
    return valid_;
}

bool Decoder::parse_header() {
    constexpr std::array<char, 20> expected = {
      'I','n','t','e','r','p','l','a','y',' ','M','V','E',' ','F','i','l','e', 0x1A, 0x00
    };

    std::array<char, 20> signature;
    input_.read(signature.data(), 20);

    if (input_.gcount() != static_cast<std::streamsize>(signature.size()) ||
    !std::equal(signature.begin(), signature.end(), expected.begin()))
    {
      spdlog::error("Invalid MVE header signature");
      return false;
    }


    std::array<char, 6> magic;
    input_.read(magic.data(), 6);
    if (input_.gcount() != 6) {
        spdlog::error("Failed to read MVE magic bytes");
        return false;
    }

    return true;
}

std::unique_ptr<Chunk> Decoder::next_chunk() {
    if (!input_ || input_.eof())
        return nullptr;

    uint16_t chunk_length = 0;
    uint16_t chunk_type = 0;

    input_.read(reinterpret_cast<char*>(&chunk_length), 2);
    input_.read(reinterpret_cast<char*>(&chunk_type), 2);

    if (input_.gcount() != 2) {
        spdlog::warn("Failed to read chunk header");
        return nullptr;
    }

    std::vector<uint8_t> chunk_data(chunk_length);
    std::streamoff chunk_start_offset = input_.tellg();

    input_.read(reinterpret_cast<char*>(chunk_data.data()), chunk_length);
    if (input_.gcount() != chunk_length) {
        spdlog::error("Failed to read full chunk data");
        return nullptr;
    }

    spdlog::info("Chunk @ offset 0x{:08x}: type = 0x{:04x}, size = {} | preview: {}", static_cast<std::uint32_t>(chunk_start_offset), chunk_type, chunk_length, hex_dump(chunk_data));

    auto chunk = std::make_unique<Chunk>(chunk_type, std::move(chunk_data));
    chunk->parse_opcodes();

    return chunk;
}

} // namespace mve
