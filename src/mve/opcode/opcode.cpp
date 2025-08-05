#include <mve/opcode/opcode.hpp>
#include <mve/opcode/opcode_end_of_stream.hpp>
#include <mve/opcode/opcode_end_of_chunk.hpp>
#include <mve/opcode/opcode_create_timer.hpp>
#include <mve/opcode/opcode_start_stop_audio.hpp>
#include <mve/opcode/opcode_initialize_audio_buffers.hpp>
#include <mve/opcode/opcode_initialize_video_buffer.hpp>
#include <mve/opcode/opcode_send_buffer_to_display.hpp>
#include <mve/opcode/opcode_audio_frame_data.hpp>
#include <mve/opcode/opcode_audio_frame_silence.hpp>
#include <mve/opcode/opcode_initialize_video_mode.hpp>
#include <mve/opcode/opcode_create_gradient.hpp>
#include <mve/opcode/opcode_set_palette.hpp>
#include <mve/opcode/opcode_set_palette_entries_compressed.hpp>
#include <mve/opcode/opcode_set_decoding_map.hpp>
#include <mve/opcode/opcode_video_data.hpp>
//#include <mve/opcode/unknown.hpp>

namespace mve {

std::unique_ptr<Opcode> decode_opcode(uint8_t opcode_type, uint8_t version, std::span<const uint8_t> payload) {
    switch (opcode_type) {
        case 0:
            return std::make_unique<OpcodeEndOfStream>(opcode_type, version, payload);
        case 1:
            return std::make_unique<OpcodeEndOfChunk>(opcode_type, version, payload);
        case 2:
            return std::make_unique<OpcodeCreateTimer>(opcode_type, version, payload);
        case 3:
            return std::make_unique<OpcodeInitializeAudioBuffers>(opcode_type, version, payload);
        case 4:
            return std::make_unique<OpcodeStartStopAudio>(opcode_type, version, payload);
        case 5:
            return std::make_unique<OpcodeInitializeVideoBuffer>(opcode_type, version, payload);
        case 7:
            return std::make_unique<OpcodeSendBufferToDisplay>(opcode_type, version, payload);
        case 8:
            return std::make_unique<OpcodeAudioFrameData>(opcode_type, version, payload);
        case 9:
            return std::make_unique<OpcodeAudioFrameSilence>(opcode_type, version, payload);
        case 0xa:
            return std::make_unique<OpcodeInitializeVideoMode>(opcode_type, version, payload);
        case 0xb:
            return std::make_unique<OpcodeCreateGradient>(opcode_type, version, payload);
        case 0xc:
            return std::make_unique<OpcodeSetPalette>(opcode_type, version, payload);
        case 0xd:
            return std::make_unique<OpcodeSetPaletteEntriesCompressed>(opcode_type, version, payload);
        case 0xf:
            return std::make_unique<OpcodeSetDecodingMap>(opcode_type, version, payload);
        case 0x11:
            return std::make_unique<OpcodeVideoData>(opcode_type, version, payload);
        default:
            return std::make_unique<Opcode>(opcode_type, version, payload);
    }
}

}
