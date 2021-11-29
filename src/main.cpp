#pragma once
#include "Chess/Chess.h"
#include "Chess/PlayerCountSelection.h"

#ifdef _WIN32 
#undef main // Undef main because of SDL library
#endif

int main(int argc, char* argv[])
{
	SDLHandler* handler = new SDLHandler(800, 800, true);
	handler->start("Chess");


	PlayerCountSelection selection = PlayerCountSelection(handler, 800, 800);
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