#include<log/log.hpp>
#include<mve/hex_dump.hpp>
#include<mve/opcode/opcode.hpp>

namespace mve {

class OpcodeInitializeVideoBuffer : public Opcode {
public:
    uint16_t x_resolution;
    uint16_t y_resolution;
    uint16_t flags;

    OpcodeInitializeVideoBuffer(uint8_t type, uint8_t version, const std::span<const uint8_t> payload);

    std::string name() const override;
    void process() const override;
};


};
