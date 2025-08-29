#pragma once
#include<mve/opcode/opcode.hpp>

namespace mve {


class OpcodeCreateGradient : public Opcode {
public:
    using Opcode::Opcode;

    std::string name() const override {
        return "OpcodeCreateGradient";
    }
};

};
