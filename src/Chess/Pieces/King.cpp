#include "Chess/Pieces/King.h"
#include "Chess/GameLogic.h"

static bool is_normal_move_possible(const Board& board, const Move& move)
{
	if ((move.fromX == move.toX) && (move.fromY == move.toY))
		return false;

	if ((abs(move.fromX - move.toX) > 1) || (abs(move.fromY - move.toY) > 1))
		return false;

	if (!is_field_occupied(board, move.toX, move.toY))
		return true;

	return pieces_have_different_color(board, move);
}

static bool is_valid_rook_for_castling(const Board& board, int rook_x, int rook_y)
{
	if (!is_field_occupied(board, rook_x, rook_y))
		return false;

	if (has_moved(board, rook_x, rook_y))
		return false;

	return true;
}

static bool is_castling_possible(const Board& board, const Move& move)
{
	const bool king_moved = has_moved(board, move.fromX, move.fromY);
	if (king_moved || move.fromY != move.toY)
		return false;
	if (abs(move.fromX - move.toX) != 2)
		return false;

	const int x_direction = (move.toX - move.fromX) / abs(move.toX - move.fromX);
	const int rookX = (x_direction > 0) ? 7 : 0;

	if (!is_valid_rook_for_castling(board, rookX, move.fromY))
		return false;

	if (pieces_have_different_color(board, Move{ move.fromX, move.fromY, rookX, move.fromY }))
		return false;

	for (int x = move.fromX + x_direction; x != rookX; x += x_direction)
	{
		if (is_field_occupied(board, x, move.fromY))
			return false;
	}

	if (is_check(board, move.fromX, move.fromY))
		return false;

	// TODO double check if this correct and a good "performant" way
	Board check_test = board;
	std::swap(check_test[move.fromX][move.fromY], check_test[move.fromX + x_direction][move.fromY]);
	if (is_check(check_test, move.fromX + x_direction, move.fromY))
		return false;

	std::swap(check_test[move.fromX + x_direction][move.fromY], check_test[move.fromX + x_direction * 2][move.fromY]);
	if (is_check(check_test, move.fromX + x_direction * 2, move.fromY))
		return false;

	return true;
}

bool King::is_move_valid(const Board& board, const Move& move)
{
	return is_normal_move_possible(board, move) || is_castling_possible(board, move);
}

void King::make_move(Board& board, const Move& move)
{
}
