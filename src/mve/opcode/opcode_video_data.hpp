#include<mve/opcode/opcode.hpp>

namespace mve {


class OpcodeVideoData : public Opcode {
public:
    using Opcode::Opcode;

    std::string name() const override {
        return "OpcodeVideoData";
    }
};

};
