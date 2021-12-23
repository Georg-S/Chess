#pragma once
// We need to define SDL_MAIN_HANDLED, to be able to execute the main function (WinMain works without this define)
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <Windows.h>
#include <memory>
#include "Chess/Chess.h"
#include "Chess/Constant.h"
#include "Chess/PlayerCountSelection.h"
#include "Chess/PlayerColorSelection.h"

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

/*
// Use WinMain instead of main, so we can not show the console window
// With main: the linker throws an error if the application is defined as Subsystem Windows
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	auto chess = create_chess_game_by_user_input();
	chess.game_loop();

	return 0;
}
*/

int main() 
{
	auto chess = create_chess_game_by_user_input();
	chess.game_loop();

	return 0;
}