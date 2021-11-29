#pragma once
#include "Chess/Chess.h"
#include "Chess/Constant.h"
#include "Chess/PlayerCountSelection.h"

#ifdef _WIN32 
#undef main // Undef main because of SDL library
#endif

int main(int argc, char* argv[])
{
	SDLHandler* handler = new SDLHandler(window_width, window_height, true);
	handler->start("Chess");

	PlayerCountSelection selection = PlayerCountSelection(handler);
	selection.createPlayerSelection();

	int player_count = -1;
	while (!handler->exit && player_count == -1) 
	{
		player_count = selection.getSelectedPlayerCount();
	}
	selection.destroy();
	handler->close();


	Chess chess;
	chess.game_loop();

	return 0;
}