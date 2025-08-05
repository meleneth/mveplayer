#include<mve/opcode/opcode.hpp>

namespace mve {


class OpcodeInitializeVideoMode : public Opcode {
public:
    using Opcode::Opcode;

    std::string name() const override {
        return "OpcodeInitializeVideoMode";
    }
};

};
