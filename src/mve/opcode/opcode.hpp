#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <span>
#include <string>

namespace mve {

class Opcode {
public:
    Opcode(uint8_t type, uint8_t version, std::span<const uint8_t> payload)
        : type_(type), version_(version), payload_(payload.begin(), payload.end()) {}

    virtual ~Opcode() = default;

    uint8_t type() const { return type_; }
    uint8_t version() const { return version_; }

    virtual std::string name() const { return "GenericOpcode"; }

    virtual void process() const { }

    const std::vector<uint8_t>& data() const { return payload_; }

protected:
    uint8_t type_;
    uint8_t version_;
    std::vector<uint8_t> payload_;
};

/// Factory function to build an opcode based on its type byte
std::unique_ptr<Opcode> decode_opcode(uint8_t type, uint8_t version, std::span<const uint8_t> payload);

} // namespace mve
