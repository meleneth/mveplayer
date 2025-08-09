#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include "mve/opcode/opcode_set_palette.hpp"
#include "mve/hex_dump.hpp" // if needed for debug logging

TEST_CASE("OpcodeSetPalette parses pal_start and pal_count correctly from raw payload") {
    using namespace mve;

    std::vector<uint8_t> raw_payload = {
        0x01, 0x00,  // pal_start = 1
        0x01, 0x00,  // pal_count = 1
        0x01, 0x00, 0x00
    };

    std::span<const uint8_t> payload(raw_payload);

    OpcodeSetPalette opcode(0x0c, 12, payload);

    REQUIRE(opcode.type() == 12);
    REQUIRE(opcode.pal_start == 1);
    REQUIRE(opcode.pal_count == 1);
    REQUIRE(opcode.data().size() == 3);  // trailing 2 bytes preserved
}
