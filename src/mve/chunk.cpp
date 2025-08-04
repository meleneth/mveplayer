#include <mve/chunk.hpp>
#include <mve/opcode/opcode.hpp>
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
    size_t offset = 0;
    opcodes_.clear();

    while (offset + 4 <= raw_data_.size()) {
        uint16_t len = raw_data_[offset] | (raw_data_[offset + 1] << 8);
        uint8_t type = raw_data_[offset + 2];
        uint8_t version = raw_data_[offset + 3];

        if (len < 4 || offset + len > raw_data_.size()) {
            spdlog::warn("Truncated or invalid opcode in chunk: offset={}, len={}", offset, len);
            break;
        }

        std::vector<uint8_t> payload(
            raw_data_.begin() + offset + 4,
            raw_data_.begin() + offset + len
        );

        auto opcode = decode_opcode(type, version, payload);
        if (opcode) {
            opcodes_.push_back(std::move(opcode));
        }

        offset += len;
    }
}

}
