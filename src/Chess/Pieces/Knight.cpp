#include "Chess/Pieces/Knight.h"
#include "Chess/GameLogic.h"

bool Knight::is_move_valid(const Board& board, const Move& move)
{
	const int xDistance = abs(move.fromX - move.toX);
	const int yDistance = abs(move.fromY - move.toY);
	if (xDistance + yDistance == 3 && xDistance != 0 && yDistance != 0)
	{
		if(!is_field_occupied(board, move.toX, move.toY))
			return true;
		if(pieces_have_different_color(board, move))
			return true;
	}
	return false;
}

void Knight::make_move(Board& board, const Move& move)
{
	move_piece_to_position(board, move);
}
