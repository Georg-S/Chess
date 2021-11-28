#include "Chess/GameLogic.h"

inline bool is_occupied(uint32_t field)
{
	return field & field_is_occupied;
}

bool is_field_occupied(const Board& board, int x, int y)
{
	return is_occupied(board[x][y]);
}

PieceColor get_piece_color(uint32_t piece)
{
	assert(is_occupied(piece));

	if (piece & color_is_black)
		return PieceColor::BLACK;
	else
		return PieceColor::WHITE;
}

PieceColor get_piece_color(const Board& board, int x, int y)
{
	return get_piece_color(board[x][y]);
}

uint32_t get_piece_type_value(uint32_t piece)
{
	assert(is_occupied(piece));
	uint32_t val = piece & piece_mask;
	assert(val);

	return val;
}

bool is_move_valid(const Board& board, const Move& move)
{
	return true;
}

void make_move(Board& board, Move& move)
{
}

bool has_pawn_reached_end_of_board(const Board& board)
{
	return false;
}

PieceColor get_next_player(PieceColor player)
{
	assert(player != PieceColor::UNDEFINED);
	if (player == PieceColor::BLACK)
		return PieceColor::WHITE;
	else if (player == PieceColor::WHITE)
		return PieceColor::BLACK;
}

bool is_game_over(const Board& board, PieceColor color)
{
	return false;
}
