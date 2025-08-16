#include<mve/opcode/opcode.hpp>

namespace mve {


class OpcodeSetPaletteEntriesCompressed : public Opcode {
public:
    using Opcode::Opcode;

    std::string name() const override {
        return "OpcodeSetPaletteEntriesCompressed";
    }
};

};
