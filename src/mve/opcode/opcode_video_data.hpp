#include<mve/opcode/opcode.hpp>

namespace mve {


class OpcodeVideoData : public Opcode {
public:
    OpcodeVideoData(uint8_t type, uint8_t version, const std::span<const uint8_t> payload);

    std::string name() const override;

    void process(MoviePlayer &movie_player) const override;
    void process_encoding_00(int x, int y, MoviePlayer &movie_player);
};

};
