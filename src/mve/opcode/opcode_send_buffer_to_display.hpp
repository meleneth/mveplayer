#include<mve/opcode/opcode.hpp>

namespace mve {


class OpcodeSendBufferToDisplay : public Opcode {
public:
    using Opcode::Opcode;

    std::string name() const override {
        return "OpcodeSendBufferToDisplay";
    }
};

};
