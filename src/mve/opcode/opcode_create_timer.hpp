#include<mve/opcode/opcode.hpp>

namespace mve {


class OpcodeCreateTimer : public Opcode {
public:
    using Opcode::Opcode;

    std::string name() const override {
        return "OpcodeCreateTimer";
    }
};

};
