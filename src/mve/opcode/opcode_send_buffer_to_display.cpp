#include<mve/opcode/opcode_send_buffer_to_display.hpp>

#include<mve/opcode/movie_player.hpp>

namespace mve {

std::string OpcodeSendBufferToDisplay::name() const {
	return "OpcodeSendBufferToDisplay";
}

void OpcodeSendBufferToDisplay::process(MoviePlayer &movie_player)
{
    movie_player.swap_buffers();
    movie_player.render_current_to_screen();
}

};
