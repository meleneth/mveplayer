#include <mve/chunk.hpp>
#include <mve/opcode/opcode.hpp>
#include <mve/hex_dump.hpp>
#include <spdlog/spdlog.h>

namespace mve {

Chunk::Chunk(uint16_t type, std::vector<uint8_t>&& data)
    : type_(type), raw_data_(std::move(data)) {}

uint16_t Chunk::type() const {
    return type_;
}

size_t Chunk::size() const {
    return raw_data_.size();
}

const std::vector<std::unique_ptr<Opcode>>& Chunk::opcodes() const {
    return opcodes_;
}

void Chunk::parse_opcodes() {
    std::size_t offset = 0;
    opcodes_.clear();

    while (offset + 4 <= raw_data_.size()) {
        const uint8_t* data = raw_data_.data() + offset;

        // Length is for payload only, does NOT include the 4-byte header
        uint16_t payload_len = data[0] | (data[1] << 8);
        uint8_t type = data[2];
        uint8_t version = data[3];

        std::size_t remaining = raw_data_.size() - offset;
        std::size_t total_len = 4 + payload_len;

        spdlog::debug("parse_opcodes: {}", hex_dump(std::span(data, std::min<std::size_t>(remaining, 16))));

        if (remaining < total_len) {
            spdlog::warn("Truncated or invalid opcode in chunk:");
            spdlog::warn("  at chunk offset     = {}", offset);
            spdlog::warn("  raw_data_.size()    = {}", raw_data_.size());
            spdlog::warn("  claimed payload_len = {}", payload_len);
            spdlog::warn("  remaining bytes     = {}", remaining);
            spdlog::warn("  type/version        = 0x{:02x} / 0x{:02x}", type, version);

            std::ostringstream bad_bytes;
            for (std::size_t i = 0; i < std::min<std::size_t>(16, remaining); ++i) {
                bad_bytes << std::hex << std::setw(2) << std::setfill('0')
                          << static_cast<int>(raw_data_[offset + i]) << " ";
            }
            spdlog::warn("  next 16 bytes: {}", bad_bytes.str());
            break;
        }

        std::vector<uint8_t> payload(
            raw_data_.begin() + offset + 4,
            raw_data_.begin() + offset + 4 + payload_len
        );

        auto opcode = decode_opcode(type, version, payload);
        if (opcode) {
            opcodes_.push_back(std::move(opcode));
        } else {
            spdlog::warn("Unknown or unhandled opcode: type=0x{:02x}, version=0x{:02x}", type, version);
        }

        offset += total_len;
    }
}

}
