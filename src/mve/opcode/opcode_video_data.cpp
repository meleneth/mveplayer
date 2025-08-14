#include <algorithm>
#include<mve/opcode/opcode_video_data.hpp>
#include<mve/opcode/movie_player.hpp>

namespace mve {

OpcodeVideoData::OpcodeVideoData(uint8_t type, uint8_t version, const std::span<const uint8_t> payload)
    : Opcode(type, version, payload)
{
}

std::string OpcodeVideoData::name() const
{
    return "OpcodeVideoData";
}

void OpcodeVideoData::process(MoviePlayer &movie_player) const
{
  (void)movie_player;
}

void OpcodeVideoData::process_encoding_00(int x, int y, MoviePlayer &movie_player)
{
  for(int i = 0; i < 8; i++) {
    auto src = std::span<uint8_t>(movie_player.current_frame->raw_data).subspan(x * 3 + ((i + y) * movie_player.pitch), 24);
    auto dst = std::span<uint8_t>(    movie_player.new_frame->raw_data).subspan(x * 3 + ((i + y) * movie_player.pitch), 24);
    std::copy_n(src.data(), src.size(), dst.data());
  }
}

void OpcodeVideoData::process_encoding_01(int x, int y, MoviePlayer &movie_player)
{
  (void)movie_player;
  (void)x;
  (void)y;
}

void OpcodeVideoData::process_encoding_02(int x, int y, MoviePlayer &movie_player)
{
  (void)movie_player;
  (void)x;
  (void)y;
  stream_index++;
}

void OpcodeVideoData::process_encoding_03(int x, int y, MoviePlayer &movie_player)
{
  (void)movie_player;
  (void)x;
  (void)y;
  stream_index++;
}

void OpcodeVideoData::process_encoding_04(int x, int y, MoviePlayer &movie_player)
{
  (void)movie_player;
  (void)x;
  (void)y;
  stream_index++;
}

void OpcodeVideoData::process_encoding_05(int x, int y, MoviePlayer &movie_player)
{
  (void)movie_player;
  (void)x;
  (void)y;
  stream_index++;
  stream_index++;
}

void OpcodeVideoData::process_encoding_06(int x, int y, MoviePlayer &movie_player)
{
  (void)movie_player;
  (void)x;
  (void)y;
}

void OpcodeVideoData::process_encoding_07(int block_x, int block_y, MoviePlayer &movie_player)
{
  int p0 = payload_[stream_index++];
  int p1 = payload_[stream_index++];

  auto &palette_entry_0 = movie_player.palette[p0];
  auto &palette_entry_1 = movie_player.palette[p1];

  auto& new_frame_data = movie_player.new_frame->raw_data;

  int base_x = block_x * 8;
  int base_y = block_y * 8;

  if (p0 <= p1) {
    for(int y = 0; y < 8 ; ++y) {
      uint8_t pattern = payload_[stream_index++];
      int mask = 128;
      for(int x = 0; x < 8 ; ++x) {
        int frame_pixel = ((base_x + x) * 3) + ((base_y + y) * movie_player.pitch);
        if(mask & pattern) {
          new_frame_data[frame_pixel    ] = palette_entry_1.r;
          new_frame_data[frame_pixel + 1] = palette_entry_1.g;
          new_frame_data[frame_pixel + 2] = palette_entry_1.b;
        } else {
          new_frame_data[frame_pixel    ] = palette_entry_0.r;
          new_frame_data[frame_pixel + 1] = palette_entry_0.g;
          new_frame_data[frame_pixel + 2] = palette_entry_0.b;
        }
        mask >>= 1;
      }
    }
  } else {
    uint8_t b0 = payload_[stream_index++];
    uint8_t b1 = payload_[stream_index++];
    std::array<uint8_t, 4> nibbles{
      static_cast<uint8_t>(b0 >> 4),
      static_cast<uint8_t>(b0 & 0x0f),
      static_cast<uint8_t>(b1 >> 4),
      static_cast<uint8_t>(b1 & 0x0f),
    };
    for(int y = 0; y < 4 ; ++y) {
      int mask = 8;
      for(int x = 0; x < 4; ++x) {
        int frame_pixel = ((base_x + (x* 2)) * 3) + ((base_y + (y * 2)) * movie_player.pitch);
        if(mask & nibbles[y]) {
          new_frame_data[frame_pixel    ] = palette_entry_0.r;
          new_frame_data[frame_pixel + 1] = palette_entry_0.g;
          new_frame_data[frame_pixel + 2] = palette_entry_0.b;

          new_frame_data[frame_pixel + 3] = palette_entry_0.r;
          new_frame_data[frame_pixel + 4] = palette_entry_0.g;
          new_frame_data[frame_pixel + 5] = palette_entry_0.b;

          new_frame_data[frame_pixel     + movie_player.pitch] = palette_entry_0.r;
          new_frame_data[frame_pixel + 1 + movie_player.pitch] = palette_entry_0.g;
          new_frame_data[frame_pixel + 2 + movie_player.pitch] = palette_entry_0.b;

          new_frame_data[frame_pixel + 3 + movie_player.pitch] = palette_entry_0.r;
          new_frame_data[frame_pixel + 4 + movie_player.pitch] = palette_entry_0.g;
          new_frame_data[frame_pixel + 5 + movie_player.pitch] = palette_entry_0.b;
        } else {
          new_frame_data[frame_pixel    ] = palette_entry_1.r;
          new_frame_data[frame_pixel + 1] = palette_entry_1.g;
          new_frame_data[frame_pixel + 2] = palette_entry_1.b;

          new_frame_data[frame_pixel + 3] = palette_entry_1.r;
          new_frame_data[frame_pixel + 4] = palette_entry_1.g;
          new_frame_data[frame_pixel + 5] = palette_entry_1.b;

          new_frame_data[frame_pixel     + movie_player.pitch] = palette_entry_1.r;
          new_frame_data[frame_pixel + 1 + movie_player.pitch] = palette_entry_1.g;
          new_frame_data[frame_pixel + 2 + movie_player.pitch] = palette_entry_1.b;

          new_frame_data[frame_pixel + 3 + movie_player.pitch] = palette_entry_1.r;
          new_frame_data[frame_pixel + 4 + movie_player.pitch] = palette_entry_1.g;
          new_frame_data[frame_pixel + 5 + movie_player.pitch] = palette_entry_1.b;
        }
        mask >>= 1;
      }
    }
  }
}

void OpcodeVideoData::set_frame_pixel(MoviePlayer &movie_player, int pixel_x, int pixel_y, bool which_palette, MPRGB8 &palette_0, MPRGB8 &palette_1)
{
    int frame_pixel = ( pixel_x * 3) + ( pixel_y * movie_player.pitch);
    auto& new_frame_data = movie_player.new_frame->raw_data;

    if(which_palette) {
      new_frame_data[frame_pixel    ] = palette_1.r;
      new_frame_data[frame_pixel + 1] = palette_1.g;
      new_frame_data[frame_pixel + 2] = palette_1.b;
    } else {
      new_frame_data[frame_pixel    ] = palette_0.r;
      new_frame_data[frame_pixel + 1] = palette_0.g;
      new_frame_data[frame_pixel + 2] = palette_0.b;
  }
}

void OpcodeVideoData::helper_08_1(int line_x, int line_y, uint8_t p0, uint8_t p1, uint8_t bitmap, MoviePlayer &movie_player)
{
    auto &palette_entry_0 = movie_player.palette[p0];
    auto &palette_entry_1 = movie_player.palette[p1];
    int mask = 128;
    for(int x = 0; x < 4; ++x) {
      set_frame_pixel(movie_player, line_x + x, line_y, bitmap & mask, palette_entry_0, palette_entry_1);
      mask >>= 1;
    }
    ++line_y;
    for(int x = 0; x < 4; ++x) {
      set_frame_pixel(movie_player, line_x + x, line_y, bitmap & mask, palette_entry_0, palette_entry_1);
      mask >>= 1;
    }
}

void OpcodeVideoData::process_encoding_08(int base_x, int base_y, MoviePlayer &movie_player)
{
  int p0 = payload_[stream_index++];
  int p1 = payload_[stream_index++];

  //auto &palette_entry_0 = movie_player.palette[p0];
  //auto &palette_entry_1 = movie_player.palette[p1];

  if(p0 <= p1) {
    int b0 = payload_[stream_index++];
    int b1 = payload_[stream_index++];

    helper_08_1(base_x, base_y,     p0, p1, b0, movie_player);
    helper_08_1(base_x, base_y + 2, p0, p1, b1, movie_player);

    p0 = payload_[stream_index++];
    p1 = payload_[stream_index++];
    b0 = payload_[stream_index++];
    b1 = payload_[stream_index++];

    helper_08_1(base_x + 4, base_y,     p0, p1, b0, movie_player);
    helper_08_1(base_x + 4, base_y + 2, p0, p1, b1, movie_player);

    p0 = payload_[stream_index++];
    p1 = payload_[stream_index++];
    b0 = payload_[stream_index++];
    b1 = payload_[stream_index++];

    helper_08_1(base_x, base_y + 4, p0, p1, b0, movie_player);
    helper_08_1(base_x, base_y + 6, p0, p1, b1, movie_player);

    p0 = payload_[stream_index++];
    p1 = payload_[stream_index++];
    b0 = payload_[stream_index++];
    b1 = payload_[stream_index++];

    helper_08_1(base_x + 4, base_y + 4, p0, p1, b0, movie_player);
    helper_08_1(base_x + 4, base_y + 6, p0, p1, b1, movie_player);
  } else {
    int b0 = payload_[stream_index++];
    int b1 = payload_[stream_index++];
    int b2 = payload_[stream_index++];
    int b3 = payload_[stream_index++];
    int p2 = payload_[stream_index++];
    int p3 = payload_[stream_index++];
    int b4 = payload_[stream_index++];
    int b5 = payload_[stream_index++];
    int b6 = payload_[stream_index++];
    int b7 = payload_[stream_index++];
    if(p2 <=p3) {
      
    } else {

    }
    (void)b0;
    (void)b1;
    (void)b2;
    (void)b3;
    (void)b4;
    (void)b5;
    (void)b6;
    (void)b7;
    (void)p0;
    (void)p1;
    (void)p2;
    (void)p3;
  }

}

void OpcodeVideoData::process_encoding_09(int x, int y, MoviePlayer &movie_player)
{
  (void)movie_player;
  (void)x;
  (void)y;
}

void OpcodeVideoData::process_encoding_0a(int x, int y, MoviePlayer &movie_player)
{
  (void)movie_player;
  (void)x;
  (void)y;
}

void OpcodeVideoData::process_encoding_0b(int block_x, int block_y, MoviePlayer &movie_player)
{
  auto& new_frame_data = movie_player.new_frame->raw_data;
  int base_x = block_x * 8;
  int base_y = block_y * 8;

  for(int y = 0; y < 8; ++y) {
    for(int x=0; x<8; ++x) {
      int frame_pixel = ((base_x + x) * 3) + ((base_y + y) * movie_player.pitch);
      auto &palette_entry = movie_player.palette[payload_[stream_index]];
      new_frame_data[frame_pixel    ] = palette_entry.r;
      new_frame_data[frame_pixel + 1] = palette_entry.g;
      new_frame_data[frame_pixel + 2] = palette_entry.b;
      stream_index++;
    }
  }
}

void OpcodeVideoData::process_encoding_0c(int block_x, int block_y, MoviePlayer &movie_player)
{
  auto& new_frame_data = movie_player.new_frame->raw_data;
  int base_x = block_x * 8;
  int base_y = block_y * 8;

  for(int y = 0; y < 4; ++y) {
    for(int x=0; x < 4; ++x) {
      int frame_pixel = ((base_x + (x * 2)) * 3) + ((base_y + (y * 2)) * movie_player.pitch);
      auto &palette_entry = movie_player.palette[payload_[stream_index]];
      new_frame_data[frame_pixel    ] = palette_entry.r;
      new_frame_data[frame_pixel + 1] = palette_entry.g;
      new_frame_data[frame_pixel + 2] = palette_entry.b;

      new_frame_data[frame_pixel + 3] = palette_entry.r;
      new_frame_data[frame_pixel + 4] = palette_entry.g;
      new_frame_data[frame_pixel + 5] = palette_entry.b;

      new_frame_data[frame_pixel + movie_player.pitch    ] = palette_entry.r;
      new_frame_data[frame_pixel + movie_player.pitch + 1] = palette_entry.g;
      new_frame_data[frame_pixel + movie_player.pitch + 2] = palette_entry.b;

      new_frame_data[frame_pixel + movie_player.pitch + 3] = palette_entry.r;
      new_frame_data[frame_pixel + movie_player.pitch + 4] = palette_entry.g;
      new_frame_data[frame_pixel + movie_player.pitch + 5] = palette_entry.b;
      stream_index++;
    }
  }
}

void OpcodeVideoData::process_encoding_0d(int block_x, int block_y, MoviePlayer &movie_player)
{
  auto& new_frame_data = movie_player.new_frame->raw_data;
  int base_x = block_x * 8;
  int base_y = block_y * 8;

  for(int y = 0; y < 2; ++y) {
    for(int x=0; x < 2; ++x) {
      int frame_pixel = ((base_x + (x * 4)) * 3) + ((base_y + (y * 4)) * movie_player.pitch);
      auto &palette_entry = movie_player.palette[payload_[stream_index]];
      new_frame_data[frame_pixel    ] = palette_entry.r;
      new_frame_data[frame_pixel + 1] = palette_entry.g;
      new_frame_data[frame_pixel + 2] = palette_entry.b;

      new_frame_data[frame_pixel + 3] = palette_entry.r;
      new_frame_data[frame_pixel + 4] = palette_entry.g;
      new_frame_data[frame_pixel + 5] = palette_entry.b;

      new_frame_data[frame_pixel + 6] = palette_entry.r;
      new_frame_data[frame_pixel + 7] = palette_entry.g;
      new_frame_data[frame_pixel + 8] = palette_entry.b;

      new_frame_data[frame_pixel + 9 ] = palette_entry.r;
      new_frame_data[frame_pixel + 10] = palette_entry.g;
      new_frame_data[frame_pixel + 11] = palette_entry.b;

      new_frame_data[frame_pixel + movie_player.pitch    ] = palette_entry.r;
      new_frame_data[frame_pixel + movie_player.pitch + 1] = palette_entry.g;
      new_frame_data[frame_pixel + movie_player.pitch + 2] = palette_entry.b;

      new_frame_data[frame_pixel + movie_player.pitch + 3] = palette_entry.r;
      new_frame_data[frame_pixel + movie_player.pitch + 4] = palette_entry.g;
      new_frame_data[frame_pixel + movie_player.pitch + 5] = palette_entry.b;

      new_frame_data[frame_pixel + movie_player.pitch + 6] = palette_entry.r;
      new_frame_data[frame_pixel + movie_player.pitch + 7] = palette_entry.g;
      new_frame_data[frame_pixel + movie_player.pitch + 8] = palette_entry.b;

      new_frame_data[frame_pixel + movie_player.pitch + 9] = palette_entry.r;
      new_frame_data[frame_pixel + movie_player.pitch + 10] = palette_entry.g;
      new_frame_data[frame_pixel + movie_player.pitch + 11] = palette_entry.b;

      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch    ] = palette_entry.r;
      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + 1] = palette_entry.g;
      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + 2] = palette_entry.b;

      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + 3] = palette_entry.r;
      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + 4] = palette_entry.g;
      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + 5] = palette_entry.b;

      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + 6] = palette_entry.r;
      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + 7] = palette_entry.g;
      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + 8] = palette_entry.b;

      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + 9] = palette_entry.r;
      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + 10] = palette_entry.g;
      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + 11] = palette_entry.b;

      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + movie_player.pitch    ] = palette_entry.r;
      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + movie_player.pitch + 1] = palette_entry.g;
      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + movie_player.pitch + 2] = palette_entry.b;

      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + movie_player.pitch + 3] = palette_entry.r;
      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + movie_player.pitch + 4] = palette_entry.g;
      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + movie_player.pitch + 5] = palette_entry.b;

      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + movie_player.pitch + 6] = palette_entry.r;
      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + movie_player.pitch + 7] = palette_entry.g;
      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + movie_player.pitch + 8] = palette_entry.b;

      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + movie_player.pitch + 9] = palette_entry.r;
      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + movie_player.pitch + 10] = palette_entry.g;
      new_frame_data[frame_pixel + movie_player.pitch + movie_player.pitch + movie_player.pitch + 11] = palette_entry.b;
      stream_index++;
    }
  }
}

void OpcodeVideoData::process_encoding_0e(int block_x, int block_y, MoviePlayer &movie_player)
{
  auto& new_frame_data = movie_player.new_frame->raw_data;
  int base_y = block_y * 8;
  (void)block_x;

  auto &palette_entry = movie_player.palette[payload_[stream_index]];
  stream_index++;

  for(int y = 0; y < 8; ++y) {
    int frame_pixel =  (base_y + y) * movie_player.pitch;

    new_frame_data[frame_pixel    ] = palette_entry.r;
    new_frame_data[frame_pixel + 1] = palette_entry.g;
    new_frame_data[frame_pixel + 2] = palette_entry.b;

    new_frame_data[frame_pixel + 3] = palette_entry.r;
    new_frame_data[frame_pixel + 4] = palette_entry.g;
    new_frame_data[frame_pixel + 5] = palette_entry.b;

    new_frame_data[frame_pixel + 6] = palette_entry.r;
    new_frame_data[frame_pixel + 7] = palette_entry.g;
    new_frame_data[frame_pixel + 8] = palette_entry.b;

    new_frame_data[frame_pixel + 9 ] = palette_entry.r;
    new_frame_data[frame_pixel + 10] = palette_entry.g;
    new_frame_data[frame_pixel + 11] = palette_entry.b;

    new_frame_data[frame_pixel + 12] = palette_entry.r;
    new_frame_data[frame_pixel + 13] = palette_entry.g;
    new_frame_data[frame_pixel + 14] = palette_entry.b;

    new_frame_data[frame_pixel + 15] = palette_entry.r;
    new_frame_data[frame_pixel + 16] = palette_entry.g;
    new_frame_data[frame_pixel + 17] = palette_entry.b;

    new_frame_data[frame_pixel + 18] = palette_entry.r;
    new_frame_data[frame_pixel + 19] = palette_entry.g;
    new_frame_data[frame_pixel + 20] = palette_entry.b;

    new_frame_data[frame_pixel + 21] = palette_entry.r;
    new_frame_data[frame_pixel + 22] = palette_entry.g;
    new_frame_data[frame_pixel + 23] = palette_entry.b;
  }
}

void OpcodeVideoData::process_encoding_0f(int block_x, int block_y, MoviePlayer &movie_player)
{
  auto& new_frame_data = movie_player.new_frame->raw_data;
  int base_y = block_y * 8;
  int base_x = block_x * 8;

  auto &palette_entry1 = movie_player.palette[payload_[stream_index++]];
  auto &palette_entry2 = movie_player.palette[payload_[stream_index++]];

  for(int y = 0; y < 4; ++y) {
    int frame_pixel =  (base_x * 3) + ((base_y + (y * 2)) * movie_player.pitch);

    new_frame_data[frame_pixel    ] = palette_entry1.r;
    new_frame_data[frame_pixel + 1] = palette_entry1.g;
    new_frame_data[frame_pixel + 2] = palette_entry1.b;

    new_frame_data[frame_pixel + 3] = palette_entry2.r;
    new_frame_data[frame_pixel + 4] = palette_entry2.g;
    new_frame_data[frame_pixel + 5] = palette_entry2.b;

    new_frame_data[frame_pixel + 6] = palette_entry1.r;
    new_frame_data[frame_pixel + 7] = palette_entry1.g;
    new_frame_data[frame_pixel + 8] = palette_entry1.b;

    new_frame_data[frame_pixel + 9 ] = palette_entry2.r;
    new_frame_data[frame_pixel + 10] = palette_entry2.g;
    new_frame_data[frame_pixel + 11] = palette_entry2.b;

    new_frame_data[frame_pixel + 12] = palette_entry1.r;
    new_frame_data[frame_pixel + 13] = palette_entry1.g;
    new_frame_data[frame_pixel + 14] = palette_entry1.b;

    new_frame_data[frame_pixel + 15] = palette_entry2.r;
    new_frame_data[frame_pixel + 16] = palette_entry2.g;
    new_frame_data[frame_pixel + 17] = palette_entry2.b;

    new_frame_data[frame_pixel + 18] = palette_entry1.r;
    new_frame_data[frame_pixel + 19] = palette_entry1.g;
    new_frame_data[frame_pixel + 20] = palette_entry1.b;

    new_frame_data[frame_pixel + 21] = palette_entry2.r;
    new_frame_data[frame_pixel + 22] = palette_entry2.g;
    new_frame_data[frame_pixel + 23] = palette_entry2.b;

    frame_pixel =  (base_x * 3) + ((base_y + (y * 2) + 1) * movie_player.pitch);

    new_frame_data[frame_pixel    ] = palette_entry2.r;
    new_frame_data[frame_pixel + 1] = palette_entry2.g;
    new_frame_data[frame_pixel + 2] = palette_entry2.b;

    new_frame_data[frame_pixel + 3] = palette_entry1.r;
    new_frame_data[frame_pixel + 4] = palette_entry1.g;
    new_frame_data[frame_pixel + 5] = palette_entry1.b;

    new_frame_data[frame_pixel + 6] = palette_entry2.r;
    new_frame_data[frame_pixel + 7] = palette_entry2.g;
    new_frame_data[frame_pixel + 8] = palette_entry2.b;

    new_frame_data[frame_pixel + 9 ] = palette_entry1.r;
    new_frame_data[frame_pixel + 10] = palette_entry1.g;
    new_frame_data[frame_pixel + 11] = palette_entry1.b;

    new_frame_data[frame_pixel + 12] = palette_entry2.r;
    new_frame_data[frame_pixel + 13] = palette_entry2.g;
    new_frame_data[frame_pixel + 14] = palette_entry2.b;

    new_frame_data[frame_pixel + 15] = palette_entry1.r;
    new_frame_data[frame_pixel + 16] = palette_entry1.g;
    new_frame_data[frame_pixel + 17] = palette_entry1.b;

    new_frame_data[frame_pixel + 18] = palette_entry2.r;
    new_frame_data[frame_pixel + 19] = palette_entry2.g;
    new_frame_data[frame_pixel + 20] = palette_entry2.b;

    new_frame_data[frame_pixel + 21] = palette_entry1.r;
    new_frame_data[frame_pixel + 22] = palette_entry1.g;
    new_frame_data[frame_pixel + 23] = palette_entry1.b;
  }
}

};
