#include <catch2/catch_test_macros.hpp>
#include <mve/chunk.hpp>
#include <mve/opcode/opcode.hpp>

TEST_CASE("Chunk parses zero-length opcodes correctly", "[Chunk]") {
    // Format: [length_lo, length_hi, type, version]
    // length = 0, type = 4, version = 0
    // length = 0, type = 1, version = 0
    std::vector<uint8_t> raw = {
        0x00, 0x00, 0x04, 0x00, // opcode #0: type 4, version 0, len = 0
        0x00, 0x00, 0x01, 0x00  // opcode #1: type 1, version 0, len = 0
    };

    mve::Chunk chunk(3, std::move(raw));
    chunk.parse_opcodes();

    const auto& opcodes = chunk.opcodes();
    REQUIRE(opcodes.size() == 2);

    SECTION("Opcode 0 has correct type and zero payload") {
        auto* op0 = dynamic_cast<mve::Opcode*>(opcodes[0].get());
        REQUIRE(op0 != nullptr);
        REQUIRE(op0->type() == 0x04);
        REQUIRE(op0->version() == 0x00);
        REQUIRE(op0->data().empty());
    }

    SECTION("Opcode 1 has correct type and zero payload") {
        auto* op1 = dynamic_cast<mve::Opcode*>(opcodes[1].get());
        REQUIRE(op1 != nullptr);
        REQUIRE(op1->type() == 0x01);
        REQUIRE(op1->version() == 0x00);
        REQUIRE(op1->data().empty());
    }
}
