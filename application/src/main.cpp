#pragma once
// We need to define SDL_MAIN_HANDLED, to be able to execute the main function (WinMain works without this define)
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <Windows.h>
#include <memory>
#include <ChessEngine.h>
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

void compare_maps(const std::map<std::string, int>& map_1, const std::map<std::string, int>& map_2) 
{
	for (const auto& elem : map_1) 
	{
		if (map_2.find(elem.first) == map_2.end())
			std::cout << elem.first << " couldn't be found in second map" << std::endl;
		else if (elem.second != map_2.at(elem.first))
			std::cout << "Values are different for element: " << elem.first << " Map 1 value: " << elem.second << " Map 2 value: " << map_2.at(elem.first) << std::endl;
	}
}

int main() 
{
	const std::string perft_str = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	ceg::ChessEngine engine;
	const int depth = 6;


	uint64_t counter = 0;
	auto old = perft_get_map(perft_str, PieceColor::WHITE, depth);
	std::cout << "Counter: " << counter << " Set size: " << old.size() << std::endl;


	auto engine_perft = engine.perft_get_map(perft_str, depth);
	std::cout << "Engine counter: " << engine_perft.size() << std::endl;

	compare_maps(old, engine_perft);
	std::cout << std::endl << std::endl;
	compare_maps(engine_perft, old);
	/*
	auto engine_perft = engine.perft_get_set(perft_str, depth);
	std::cout << "Engine counter: " << engine_perft.size() << std::endl;

	for (auto& elem : boards_set)
	{
		if (engine_perft.find(elem) == engine_perft.end())
			std::cout << elem << std::endl;
	}
	*/


	return 0;
}