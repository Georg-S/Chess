#pragma once
#include <memory>
#include "GameLogic.h"
#include "SDL/SDLHandler.h"
#include "Board.h"
#include "RenderInformation.h"

class Renderer
{
public:
	Renderer();
	void render(const RenderInformation& renderInfo);
	//		void renderPromotionSelection(PieceColor color);
	int getWindowWidth();
	int getWindowHeight();
	bool update_quit();
	bool is_quit();
	void quit();

private:
	void render_chess_board();
	void render_pieces(const Board& board);
	void render_piece(const Board& board, int x, int y);
	void render_pieces_with_selected_on_mouse_position(const RenderInformation& renderInfo);
//	void renderPreviousMove(const Move& previousMove);
	void render_piece_on_mouse_position(uint32_t piece, int mouseX, int mouseY);
	std::string get_file_string(uint32_t piece) const;
	std::string get_color_string(uint32_t piece) const;
	std::string get_piece_type_string(uint32_t piece) const;

	const int window_width = 800;
	const int window_height = 800;
	int piece_width;
	int piece_height;
	std::unique_ptr<SDLHandler> sdl_handler;
};
