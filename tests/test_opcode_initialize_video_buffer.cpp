#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include "mve/opcode/opcode_initialize_video_buffer.hpp"
#include "mve/hex_dump.hpp" // if needed for debug logging

TEST_CASE("OpcodeInitializeVideoBuffer parses x/y/flags correctly from raw payload") {
    using namespace mve;

    // Raw opcode payload (not the full chunk):
    // x = 80 (0x0050), y = 40 (0x0028), flags = 1 (0x0001), trailing = 0x00 0x00
    std::vector<uint8_t> raw_payload = {
        0x50, 0x00,  // x = 80
        0x28, 0x00,  // y = 40
        0x01, 0x00,  // flags = 1
        0x00, 0x00   // trailing bytes (unknown)
    };

    std::span<const uint8_t> payload(raw_payload);

    OpcodeInitializeVideoBuffer opcode(5, 2, payload);

    REQUIRE(opcode.x_resolution == 80);
    REQUIRE(opcode.y_resolution == 40);
    REQUIRE(opcode.flags == 1);
    REQUIRE(opcode.data().size() == 2);  // trailing 2 bytes preserved
}
