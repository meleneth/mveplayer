#include<mve/opcode/opcode.hpp>

namespace mve {


class OpcodeSetDecodingMap : public Opcode {
public:
    using Opcode::Opcode;

    std::string name() const override {
        return "OpcodeSetDecodingMap";
    }
};

};
