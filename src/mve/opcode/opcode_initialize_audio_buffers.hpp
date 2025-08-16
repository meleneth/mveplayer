#include<mve/opcode/opcode.hpp>

namespace mve {


class OpcodeInitializeAudioBuffers : public Opcode {
public:
    using Opcode::Opcode;

    std::string name() const override {
        return "OpcodeInitializeAudioBuffers";
    }
};

};
