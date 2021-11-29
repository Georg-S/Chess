#pragma once
#include <memory>
#include "GameLogic.h"
#include "SDL/SDLHandler.h"
#include "Board.h"
#include "RenderInformation.h"
#include "Constant.h"

class Renderer
{
public:
	Renderer();
	Renderer(std::unique_ptr<SDLHandler> handler);
	void render(const RenderInformation& renderInfo);
	void render_promotion_selection(PieceColor color);
	int getWindowWidth();
	int getWindowHeight();
	bool is_quit();
	void quit();

private:
	void render_chess_board();
	void render_pieces(const Board& board);
	void render_piece(const Board& board, int x, int y);
	void render_pieces_with_selected_on_mouse_position(const RenderInformation& renderInfo);
	void render_previous_move(const Move& previousMove);
	void render_piece_on_mouse_position(uint32_t piece, int mouseX, int mouseY);
	void render_all_possible_moves_for_selected_piece(const Board& board, int selected_x, int selected_y);
	void render_checkmate();
	void render_stalemate();
	std::string get_file_string(uint32_t piece) const;
	std::string get_file_string(uint32_t piece_type, PieceColor piece_color);
	std::string get_color_string(PieceColor color) const;
	std::string get_piece_type_string(uint32_t piece_type) const;

	int piece_width = window_width / board_width;
	int piece_height = window_height / board_height;
	std::unique_ptr<SDLHandler> sdl_handler;
};
