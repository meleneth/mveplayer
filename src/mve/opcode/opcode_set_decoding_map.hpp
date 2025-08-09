#include<mve/opcode/opcode.hpp>

namespace mve {

class MoviePlayer;
class OpcodeSetDecodingMap : public Opcode {
public:
    using Opcode::Opcode;

    std::string name() const override;
    void process(MoviePlayer &movie_player) const override;
};

};
