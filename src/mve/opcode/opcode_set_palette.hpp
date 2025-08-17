#include<mve/opcode/opcode.hpp>

namespace mve {

class OpcodeSetPalette : public Opcode {
public:
    OpcodeSetPalette(uint8_t type, uint8_t version, const std::span<const uint8_t> payload);

    std::string name() const override;
    void process(MoviePlayer &movie_player) override;

    uint16_t pal_start;
    uint16_t pal_count;
};

};
