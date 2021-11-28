#include "Chess/Pieces/King.h"
#include "Chess/GameLogic.h"

static bool is_normal_move_possible(const Board& board, const Move& move) 
{
	if ((move.fromX == move.toX) && (move.fromY == move.toY))
		return false;

	if ((abs(move.fromX - move.toX) > 1) || (abs(move.fromY - move.toY) > 1))
		return false;

	if(!is_field_occupied(board, move.toX, move.toY))
		return true;
	
	return pieces_have_different_color(board, move);
}

static bool is_castling_possible(const Board& board, const Move& move) 
{
	return false;
}

bool King::is_move_valid(const Board& board, const Move& move)
{
    return is_normal_move_possible(board, move) || is_castling_possible(board, move);
}

void King::make_move(Board& board, const Move& move)
{
}
