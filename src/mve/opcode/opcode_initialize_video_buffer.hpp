#include<mve/opcode/opcode.hpp>

namespace mve {


class OpcodeInitializeVideoBuffer : public Opcode {
public:
    using Opcode::Opcode;

    std::string name() const override {
        return "OpcodeInitializeVideoBuffer";
    }
};

};
