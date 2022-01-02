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

	ceg::PieceColor player_color = ceg::PieceColor::WHITE;

	if (player_count == 1)
	{
		PlayerColorSelection color_selection = PlayerColorSelection(handler.get());
		color_selection.createColorSelection();

		while (!handler->exit && !color_selection.color_selected())
			color_selection.update();

		player_color = color_selection.getSelectedColor();
	}

	return Chess(std::move(handler), player_count, player_color);
}

// Use WinMain instead of main, so we can not show the console window
// With main: the linker throws an error if the application is defined as Subsystem Windows
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	auto chess = create_chess_game_by_user_input();
	chess.game_loop();

	return 0;
}

/*
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
	Chess chess = create_chess_game_by_user_input();
	chess.game_loop();

#if 0
	const std::string perft_str = "8/5p2/8/2k3P1/p3K3/8/1P6/8 b - -";
	ceg::ChessEngine engine;
	const int depth = 5;

	uint64_t counter = perft(perft_str, PieceColor::BLACK, depth);
	std::cout << "Counter: " << counter << std::endl;
	uint64_t counter = 0;
	auto old = perft_get_map(perft_str, PieceColor::WHITE, depth);
	std::cout << "Counter: " << counter << " Set size: " << old.size() << std::endl;


	auto engine_perft = engine.perft_get_map(perft_str, depth);
	std::cout << "Engine counter: " << engine_perft.size() << std::endl;

	compare_maps(old, engine_perft);
	std::cout << std::endl << std::endl;
	compare_maps(engine_perft, old);
#endif

	return 0;
}
*/