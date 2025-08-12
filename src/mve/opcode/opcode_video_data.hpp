#include<mve/opcode/opcode.hpp>

namespace mve {


class OpcodeVideoData : public Opcode {
public:
    OpcodeVideoData(uint8_t type, uint8_t version, const std::span<const uint8_t> payload);

    std::string name() const override;

    void process(MoviePlayer &movie_player) const override;
    void process_encoding_00(int x, int y, MoviePlayer &movie_player);
    void process_encoding_01(int x, int y, MoviePlayer &movie_player);
    void process_encoding_02(int x, int y, MoviePlayer &movie_player);
    void process_encoding_03(int x, int y, MoviePlayer &movie_player);
    void process_encoding_04(int x, int y, MoviePlayer &movie_player);
    void process_encoding_05(int x, int y, MoviePlayer &movie_player);
    void process_encoding_06(int x, int y, MoviePlayer &movie_player);
    void process_encoding_07(int x, int y, MoviePlayer &movie_player);
    void process_encoding_08(int x, int y, MoviePlayer &movie_player);
    void process_encoding_09(int x, int y, MoviePlayer &movie_player);
    void process_encoding_0a(int x, int y, MoviePlayer &movie_player);
    void process_encoding_0b(int x, int y, MoviePlayer &movie_player);
    void process_encoding_0c(int x, int y, MoviePlayer &movie_player);
    void process_encoding_0d(int x, int y, MoviePlayer &movie_player);
    void process_encoding_0e(int x, int y, MoviePlayer &movie_player);
    void process_encoding_0f(int x, int y, MoviePlayer &movie_player);

    uint16_t stream_index = 0;
};

};
