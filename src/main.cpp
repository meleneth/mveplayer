#include <fstream>
#include <iostream>

#include <log/log.hpp>
#include <mve/decoder.hpp>

int main(int argc, char* argv[]) {
    spdlog::set_level(spdlog::level::info);
    spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");

    if (argc < 2) {
        spdlog::error("Usage: {} <filename.mve>", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        spdlog::error("Failed to open file: {}", filename);
        return 1;
    }

    mve::Decoder decoder(file);
    if (!decoder.valid()) {
        spdlog::error("Invalid MVE file header");
        return 1;
    }

    size_t chunk_index = 0;
    while (auto chunk = decoder.next_chunk()) {
        spdlog::info("Chunk {}: type=0x{:04x}", chunk_index++, chunk->type());
        int opcode_index = 0;
        for(const auto& opcode : chunk->opcodes()) {
          spdlog::info("  Opcode #{} - {}: length={} type={} version={}", opcode_index++, opcode->name(), opcode->data().size(), opcode->type(), opcode->version());
          opcode->process();
        }
    }

    spdlog::info("Done.");
    return 0;
}
