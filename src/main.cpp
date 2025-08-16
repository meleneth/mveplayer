#include <fstream>
#include <iostream>

#include <CLI/CLI.hpp>

#include <log/log.hpp>
#include <mve/decoder.hpp>
#include <mve/opcode/movie_player.hpp>

int main(int argc, char* argv[]) {
    CLI::App app{"MVEPlayer"};

    bool debug = false;
    std::string filename;

    app.add_flag("-d,--debug", debug, "Enable debug logging");
    app.add_option("input", filename, "Path to MVE file")
      ->required()
      ->check(CLI::ExistingFile);

    CLI11_PARSE(app, argc, argv);

    spdlog::set_level(debug ? spdlog::level::debug : spdlog::level::info);
    spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");
    spdlog::info("Starting up...");


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

    mve::MoviePlayer movie_player;

    size_t chunk_index = 0;
    while (auto chunk = decoder.next_chunk()) {
        spdlog::info("Chunk {}: type=0x{:04x}", chunk_index++, chunk->type());
        int opcode_index = 0;
        for(const auto& opcode : chunk->opcodes()) {
          spdlog::info("  Opcode #{} - {}: length={} type={} version={}", opcode_index++, opcode->name(), opcode->data().size(), opcode->type(), opcode->version());
          opcode->process(movie_player);
        }
    }

    spdlog::info("Done.");
    return 0;
}
