#pragma once
#include <memory>
#include "Chess/Chess.h"
#include "Chess/Constant.h"
#include "Chess/PlayerCountSelection.h"
#include "Chess/PlayerColorSelection.h"

#ifdef _WIN32 
#undef main // Undef main because of SDL library
#endif

Chess create_chess_game_by_user_input() 
{
	auto handler = std::make_unique<SDLHandler>(window_width, window_height, true);
	handler->start("Chess");

	PlayerCountSelection selection = PlayerCountSelection(handler.get());
	selection.createPlayerSelection();

	int player_count = -1;
	while (!handler->exit && player_count == -1)
	{
		player_count = selection.getSelectedPlayerCount();
	}
	selection.destroy();

	PieceColor player_color = PieceColor::WHITE;

	if (player_count == 1)
	{
		PieceColor color = PieceColor::UNDEFINED;

		PlayerColorSelection color_selection = PlayerColorSelection(handler.get());
		color_selection.createColorSelection();

		while (!handler->exit && (color == PieceColor::UNDEFINED))
			color = color_selection.getSelectedColor();

		player_color = color;
	}

	return Chess(std::move(handler), player_count, player_color);
}

int main(int argc, char* argv[])
{
	auto chess = create_chess_game_by_user_input();
	chess.game_loop();

	return 0;
}