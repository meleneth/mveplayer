#include <mve/opcode/opcode.hpp>
//#include <mve/opcode/video.hpp>
//#include <mve/opcode/unknown.hpp>

namespace mve {

std::unique_ptr<Opcode> decode_opcode(uint8_t opcode_type, uint8_t version, std::span<const uint8_t> payload) {
    switch (opcode_type) {
        //case 7: // VideoData
        //    return std::make_unique<VideoOpcode>(version, payload);

        // case 1: return std::make_unique<CreateTimerOpcode>(...);
        // case 2: return std::make_unique<InitAudioBuffersOpcode>(...);

        default:
            return std::make_unique<Opcode>(opcode_type, version, payload);
    }
}

}
