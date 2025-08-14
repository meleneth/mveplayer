#include<mve/opcode/opcode.hpp>
#include<mve/opcode/movie_player.hpp>

namespace mve {


class OpcodeVideoData : public Opcode {
public:
    OpcodeVideoData(uint8_t type, uint8_t version, const std::span<const uint8_t> payload);

    std::string name() const override;

    void set_frame_pixel(MoviePlayer &movie_player, int pixel_x, int pixel_y, bool which_palette, MPRGB8 &palette_0, MPRGB8 &palette_1);

    void process(MoviePlayer &movie_player) const override;
    void process_encoding_00(int x, int y, MoviePlayer &movie_player);
    void process_encoding_01(int x, int y, MoviePlayer &movie_player);
    void process_encoding_02(int x, int y, MoviePlayer &movie_player);
    void process_encoding_03(int x, int y, MoviePlayer &movie_player);
    void process_encoding_04(int x, int y, MoviePlayer &movie_player);
    void process_encoding_05(int x, int y, MoviePlayer &movie_player);
    void process_encoding_06(int x, int y, MoviePlayer &movie_player);
    void process_encoding_07(int x, int y, MoviePlayer &movie_player);
    void helper_08_1(int line_x, int line_y, uint8_t p0, uint8_t p1, uint8_t bitmap, MoviePlayer &movie_player);
    void helper_08_2(int line_x, int line_y, uint8_t p0, uint8_t p1, uint8_t bitmap, MoviePlayer &movie_player);
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
