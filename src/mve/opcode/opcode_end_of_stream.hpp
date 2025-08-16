#include<mve/opcode/opcode.hpp>

namespace mve {


class OpcodeEndOfStream : public Opcode {
public:
    using Opcode::Opcode;

    std::string name() const override {
        return "OpcodeEndOfStream";
    }
};

};
