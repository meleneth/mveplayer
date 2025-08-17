#include<mve/opcode/opcode.hpp>

namespace mve {


class OpcodeInitializeVideoMode : public Opcode {
public:
    OpcodeInitializeVideoMode(uint8_t type, uint8_t version, const std::span<const uint8_t> payload);
    std::string name() const override;
    void process(MoviePlayer &movie_player) override;

    uint16_t x_resolution;
    uint16_t y_resolution;
    uint16_t flags;
};

};
