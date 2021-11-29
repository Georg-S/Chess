#include "Chess/Renderer.h"

Renderer::Renderer()
{
	sdl_handler = std::make_unique<SDLHandler>(window_width, window_height, true);
	piece_width = window_width / board_width;
	piece_height = window_height / board_height;
	sdl_handler->start("Chess");
}

void Renderer::render(const RenderInformation& renderInfo)
{
	sdl_handler->clear();
	render_chess_board();

	if (renderInfo.previousMove.fromX != -1)
		render_previous_move(renderInfo.previousMove);

	if (renderInfo.selectedPieceY == -1 || renderInfo.selectedPieceX == -1) 
	{
		render_pieces(renderInfo.board);
	}
	else 
	{
		render_pieces_with_selected_on_mouse_position(renderInfo);
		render_all_possible_moves_for_selected_piece(renderInfo.board, renderInfo.selectedPieceX, renderInfo.selectedPieceY);
	}

	sdl_handler->updateRendering();
}

void Renderer::render_chess_board()
{
	sdl_handler->createAndPushBackRenderElement("Images/Board.png", 0, 0, window_width, window_height);
}

void Renderer::render_pieces(const Board& board)
{
	for (int x = 0; x < board_width; x++)
	{
		for (int y = 0; y < board_height; y++)
		{
			if (is_field_occupied(board, x, y))
				render_piece(board, x, y);
		}
	}
}

void Renderer::render_piece(const Board& board, int x, int y)
{
	auto piece = board[x][y];
	std::string fileString = get_file_string(piece);
	sdl_handler->createAndPushBackRenderElement(fileString, piece_width * x, piece_height * y, piece_width, piece_height);
}

std::string Renderer::get_file_string(uint32_t piece) const
{
	uint32_t piece_type = get_piece_type_value(piece);
	PieceColor color = get_piece_color(piece);

	return "Images/" + get_piece_type_string(piece_type) + "_" + get_color_string(color) + ".png";
}

std::string Renderer::get_file_string(uint32_t piece_type, PieceColor piece_color)
{
	return "Images/" + get_piece_type_string(piece_type) + "_" + get_color_string(piece_color) + ".png";
}

std::string Renderer::get_color_string(PieceColor color) const
{
	if (color == PieceColor::WHITE)
		return "white";
	else if (color == PieceColor::BLACK)
		return "black";
}

std::string Renderer::get_piece_type_string(uint32_t piece_type) const
{
	switch (piece_type)
	{
	case pawn_bit:		return "Pawn";
	case knight_bit:	return "Knight";
	case queen_bit:		return "Queen";
	case king_bit:		return "King";
	case bishop_bit:	return "Bishop";
	case rook_bit:		return "Rook";
	default:		assert(0);
	}
	return "";
}

void Renderer::render_pieces_with_selected_on_mouse_position(const RenderInformation& renderInfo)
{
	uint32_t foreGroundPiece;

	for (int x = 0; x < board_width; x++)
	{
		for (int y = 0; y < board_height; y++)
		{
			if (x == renderInfo.selectedPieceX && y == renderInfo.selectedPieceY)
				foreGroundPiece = renderInfo.board[x][y];
			else if (is_field_occupied(renderInfo.board, x, y))
				render_piece(renderInfo.board, x, y);
		}
	}
	render_piece_on_mouse_position(foreGroundPiece, renderInfo.mousePositionX, renderInfo.mousePositionY);
}

void Renderer::render_piece_on_mouse_position(uint32_t piece, int mouseX, int mouseY)
{
	std::string fileString = get_file_string(piece);
	sdl_handler->createAndPushBackRenderElement(fileString, mouseX - (piece_width / 2), mouseY - (piece_height / 2), piece_width, piece_height);
}

void Renderer::render_all_possible_moves_for_selected_piece(const Board& board, int selected_x, int selected_y)
{
	std::vector<Move> possible_moves;
	get_all_possible_moves_for_piece(board, possible_moves, selected_x, selected_y);

	for (const auto& move : possible_moves) 
	{
		sdl_handler->createAndPushBackRenderElement("Images/PossibleMove.png", piece_width * move.toX, piece_height * move.toY
			, piece_width, piece_height);
	}
}

void Renderer::render_previous_move(const Move& previousMove)
{
	sdl_handler->createAndPushBackRenderElement("Images/PreviousMove.png", piece_width * previousMove.fromX, piece_height * previousMove.fromY
		, piece_width, piece_height);

	sdl_handler->createAndPushBackRenderElement("Images/PreviousMove.png", piece_width * previousMove.toX, piece_height * previousMove.toY
		, piece_width, piece_height);
}

int Renderer::getWindowWidth()
{
	return this->window_width;
}

int Renderer::getWindowHeight()
{
	return this->window_height;
}

void Renderer::render_promotion_selection(PieceColor color)
{
	sdl_handler->clear();
	sdl_handler->createAndPushBackRenderElement("Images/background.png", 0, 0, window_width, window_height);

	std::string queenStr = get_file_string(queen_bit, color);
	std::string rookStr = get_file_string(rook_bit, color);
	std::string knightStr = get_file_string(knight_bit, color);
	std::string  bishopStr = get_file_string(bishop_bit, color);

	sdl_handler->createAndPushBackRenderElement(queenStr, 0, 0, window_width / 2, window_height / 2);
	sdl_handler->createAndPushBackRenderElement(rookStr, window_width / 2, 0, window_width / 2, window_height / 2);
	sdl_handler->createAndPushBackRenderElement(knightStr, 0, window_height / 2, window_width / 2, window_height / 2);
	sdl_handler->createAndPushBackRenderElement(bishopStr, window_width / 2, window_height / 2, window_width / 2, window_height / 2);

	sdl_handler->updateRendering();
}

bool Renderer::update_quit()
{
	sdl_handler->updateQuit();
	if (sdl_handler->exit)
		sdl_handler->close();

	return sdl_handler->exit;
}

bool Renderer::is_quit()
{
	return sdl_handler->exit;
}

void Renderer::quit()
{
	sdl_handler->close();
}
