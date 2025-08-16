#include<mve/opcode/opcode.hpp>

namespace mve {


class OpcodeAudioFrameData : public Opcode {
public:
    using Opcode::Opcode;

    std::string name() const override {
        return "OpcodeAudioFrameData";
    }
};

};
