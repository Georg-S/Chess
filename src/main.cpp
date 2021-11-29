#pragma once
#include <memory>
#include "Chess/Chess.h"
#include "Chess/Constant.h"
#include "Chess/PlayerCountSelection.h"

#ifdef _WIN32 
#undef main // Undef main because of SDL library
#endif

int main(int argc, char* argv[])
{
	auto handler = std::make_unique<SDLHandler>(window_width, window_height, true);
	handler->start("Chess");

	PlayerCountSelection selection = PlayerCountSelection(handler.get());
	selection.createPlayerSelection();

	int player_count = -1;
	while (!handler->exit && player_count == -1) 
	{
		if (player_count == -1) 
		{
			player_count = selection.getSelectedPlayerCount();
		}
	}
	selection.destroy();



	Chess chess = Chess(std::move(handler), player_count);
	chess.game_loop();

	return 0;
}