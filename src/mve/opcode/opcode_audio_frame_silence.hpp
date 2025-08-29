#pragma once
#include<mve/opcode/opcode.hpp>

namespace mve {


class OpcodeAudioFrameSilence : public Opcode {
public:
    using Opcode::Opcode;

    std::string name() const override {
        return "OpcodeAudioFrameSilence";
    }
};

};
