#include <spdlog/spdlog.h>
#include <mve/opcode/video_opcode.hpp>

namespace mve {

VideoOpcode::VideoOpcode(const std::vector<uint8_t>& data)
    : raw_data(data) {}

void VideoOpcode::execute() {
    spdlog::debug("Executing video opcode with {} bytes", raw_data.size());
    // TODO: decoding logic
}

}
