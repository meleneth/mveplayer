#include "scanner_b.hpp"
#include <log/log.hpp>

namespace mve {

void ScannerB::saw_opcode(int block_x, int block_y, int chunk_no, int stream_index, int opcode)
{
  if(chunk_no != longest_b_run_chunk_no) {
    this_b_run = 0;
  }
  if(opcode == 0xb) {
    if(this_b_run == 0){
      this_b_run_block_x = block_x;
      this_b_run_block_y = block_y;
      this_b_run_stream_index = stream_index;
    } 
    this_b_run++;
    if(this_b_run > longest_b_run) {
      longest_b_run_stream_index = this_b_run_stream_index;
      longest_b_run_chunk_no = chunk_no;
      longest_b_run_block_x = this_b_run_block_x;
      longest_b_run_block_y = this_b_run_block_y;
      longest_b_run = this_b_run;
    }
  }else{
    this_b_run = 0;
  }
}

void ScannerB::report()
{
  spdlog::info("Chunk {} had highest run of b at {} encoding blocks in a row, stream_index is {} - starting at {}, {}",
		  longest_b_run_chunk_no,
		  longest_b_run,
		  longest_b_run_stream_index,
		  longest_b_run_block_x,
		  longest_b_run_block_y);
}

}
