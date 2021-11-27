#include "Chess/GameLogic.h"

inline bool is_occupied(uint32_t field)
{
	return field & field_is_occupied;
}

bool is_field_occupied(Board board, int x, int y)
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

uint32_t get_piece_type_value(uint32_t piece)
{
	assert(is_occupied(piece));
	uint32_t val = piece & piece_mask;
	assert(val);

	return val;
}
