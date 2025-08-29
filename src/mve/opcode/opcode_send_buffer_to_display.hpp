#pragma once
#include<mve/opcode/opcode.hpp>
#include<mve/opcode/movie_player.hpp>

namespace mve {


class OpcodeSendBufferToDisplay : public Opcode {
public:
    using Opcode::Opcode;

    std::string name() const override;
    virtual void process(MoviePlayer &movie_player) override;
};

};
