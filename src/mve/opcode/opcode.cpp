#include <mve/opcode/opcode.hpp>
#include <mve/opcode/video_opcode.hpp>
// Add other opcode includes here

namespace mve {

std::unique_ptr<Opcode> decode_opcode(const Chunk& chunk) {
    switch (chunk.opcode) {
        case OpcodeType::VideoData:
            return std::make_unique<VideoOpcode>(chunk.data);
        default:
            return nullptr;
    }
}

} // namespace mve
