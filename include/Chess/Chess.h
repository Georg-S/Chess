#pragma once
#include <memory>
#include "Board.h"
#include "Renderer.h"
#include "GameLogic.h"
#include "SDL/Mouse.h"

class Chess
{
public:
	Chess();
	Chess(std::unique_ptr<SDLHandler> sdl_handler, int player_count, PieceColor player_color = PieceColor::WHITE);

	void game_loop();
private:
	void update_1_player_game();
	void update_2_player_game();
	void update_ai_move();
	void update_human_move();
	Move get_human_move();
	bool is_valid_move(const Move& move);
	bool is_valid_board_pos(int x, int y);
	void handle_promo_selection(Board& board, int posx, int posy);
	uint32_t get_piece_from_promo_selection(int mouseX, int mouseY);
	void handle_game_over();
	int convert_mouse_position_x_to_board_position(int mouse_x);
	int convert_mouse_position_y_to_board_position(int mouse_y);

	Board board;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<RenderInformation> render_info;
	int player_count = 2;
	PieceColor current_player = PieceColor::WHITE;
	Move previous_move{-1, -1, -1, -1};
	Move pending_move{-1, -1, -1, -1};
	Mouse mouse;
};