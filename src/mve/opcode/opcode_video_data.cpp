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

void OpcodeVideoData::process_encoding_07(int x, int y, MoviePlayer &movie_player)
{
  (void)movie_player;
  (void)x;
  (void)y;
  int p0 = payload_[stream_index++];
  int p1 = payload_[stream_index++];
  if (p0 <= p1) {
    stream_index += 8;
  } else {
    stream_index += 2;
  }
}

void OpcodeVideoData::process_encoding_08(int x, int y, MoviePlayer &movie_player)
{
  (void)movie_player;
  (void)x;
  (void)y;
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
