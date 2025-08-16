#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include "mve/decoder.hpp"
#include <log/log.hpp>

TEST_CASE("Decoder parses a synthetic valid MVE stream") {
    using namespace mve;
    spdlog::set_level(spdlog::level::debug);
    spdlog::flush_on(spdlog::level::debug); // flush every message immediately


    // MVE Header: "Interplay MVE File\x1A\0" + 6 magic bytes
    std::vector<uint8_t> fake_mve_data = {
        'I','n','t','e','r','p','l','a','y',' ','M','V','E',' ','F','i','l','e',0x1A,0x00,
        0x00, 0x1A, 0x00, 0x01, 0x33, 0x11,  // magic (little-endian words)

        // Chunk: [len = 4], [type = 3 (video data)]
        0x04, 0x00, 0x03, 0x00,

        // Opcode: [len = 0], [opcode = 1], [version = 0]
        0x00, 0x00, 0x01, 0x00
    };

    std::istringstream stream(std::string(reinterpret_cast<char*>(fake_mve_data.data()), fake_mve_data.size()));
    Decoder decoder(stream);

    REQUIRE(decoder.valid());

    auto chunk = decoder.next_chunk();
    REQUIRE(chunk != nullptr);
    REQUIRE(chunk->type() == 3);
    REQUIRE(chunk->size() == 4);
}
