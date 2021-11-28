#include "Chess/Pieces/Pawn.h"
#include "Chess/GameLogic.h"

static bool en_passant_possible(const Board& board, const Move& move) 
{
	const int y_distance = abs(get_y_distance(move));
	const int en_passant_direction = get_en_passant_direction(board, move.fromX, move.fromY);
	if (en_passant_direction == 0)
		return false;

	if ((move.toX == move.fromX + en_passant_direction) && (y_distance == 1))
		return true;

	return false;
}

static bool is_normal_move_possible(const Board& board, const Move& move) 
{
	const auto [x_direction, y_direction] = get_direction(move);
	const int x_distance = abs(get_x_distance(move));
	const int y_distance = abs(get_y_distance(move));

	if (x_distance == 0)
	{
		if (is_field_occupied(board, move.fromX, move.fromY + y_direction))
			return false;

		if (y_distance == 1)
			return true;

		if (y_distance == 2) 
		{
			if (has_moved(board, move.fromX, move.fromY))
				return false;

			return !is_field_occupied(board, move.toX, move.toY);
		}
	}

	if ((y_distance == 1) && is_field_occupied(board, move.toX, move.toY) && pieces_have_different_color(board, move))
		return true;

	return false;
}

bool Pawn::is_move_valid(const Board& board, const Move& move)
{
	const PieceColor color = get_piece_color(board, move.fromX, move.fromY);
	const auto [x_distance, y_distance] = get_distance(move);
	if (abs(x_distance) > 1)
		return false;

	if (y_distance == 0 || abs(y_distance) > 2)
		return false;
	
	if ((y_distance > 0) && color != PieceColor::BLACK)
		return false;

	if ((y_distance < 0) && color != PieceColor::WHITE)
		return false;

	return is_normal_move_possible(board, move) || en_passant_possible(board, move);
}
