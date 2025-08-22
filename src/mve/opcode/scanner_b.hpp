#pragma once

#include<SDL.h>

#include <cstdint>
#include <vector>
#include <memory>

#include <mve/opcode/buffer.hpp>

namespace mve {

class ScannerB {
public:
  void saw_opcode(int block_x, int block_y, int chunk_no, int stream_index, int opcode);
  void report();

  int chunk_no = 0;
  int longest_b_run = 0;
  int longest_b_run_chunk_no = 0;
  int longest_b_run_block_x = 0;
  int longest_b_run_block_y = 0;
  int longest_b_run_stream_index = 0;
  int this_b_run = 0;
  int this_b_run_block_x = 0;
  int this_b_run_block_y = 0;
  int this_b_run_stream_index = 0;
};

}
