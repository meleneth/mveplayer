#pragma once
#include <vector>
#include <mve/opcode/opcode.hpp>

namespace mve {

class VideoOpcode : public Opcode {
public:
    explicit VideoOpcode(const std::vector<uint8_t>& data);
    void execute() override;

private:
    std::vector<uint8_t> raw_data;
};

}
