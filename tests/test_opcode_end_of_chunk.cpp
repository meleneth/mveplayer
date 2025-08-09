// tests/opcode_set_decoding_map.test.cpp
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <vector>

#include<mve/opcode/opcode_set_decoding_map.hpp>
#include<mve/opcode/opcode_end_of_chunk.hpp>
#include<mve/opcode/movie_player.hpp>

TEST_CASE("OpcodeEndOfChunk sets the decoding_map on MoviePlayer to nullptr") {
    mve::MoviePlayer movie_player;
    std::vector<uint8_t> raw_payload = {
    };
    std::span<const uint8_t> payload(raw_payload);

    mve::OpcodeSetDecodingMap set_decoding_map_opcode(0xf, 0, payload);
    mve::OpcodeEndOfChunk opcode(1, 0, payload);
  
    set_decoding_map_opcode.process(movie_player);
    REQUIRE(movie_player.decoding_map != nullptr);

    opcode.process(movie_player);
    REQUIRE(movie_player.decoding_map == nullptr);
}
