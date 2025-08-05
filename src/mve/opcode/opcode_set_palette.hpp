#include<mve/opcode/opcode.hpp>

namespace mve {


class OpcodeSetPalette : public Opcode {
public:
    using Opcode::Opcode;

    std::string name() const override {
        return "OpcodeSetPalette";
    }
};

};
