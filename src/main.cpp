#pragma once
#include "Chess/Chess.h"

#ifdef _WIN32 
#undef main // Undef main because of SDL library
#endif

int main(int argc, char* argv[])
{
	Chess chess;
	chess.game_loop();

	return 0;
}