#include "Chess/Pieces/Bishop.h"
#include "Chess/GameLogic.h"

bool Bishop::is_move_valid(const Board& board, const Move& move)
{
	const auto [distance_x, distance_y] = get_distance(move);

	if (abs(distance_x) != abs(distance_y))
		return false;

	return direct_move_possible(board, move);
}

void Bishop::make_move(Board& board, const Move& move)
{
	move_piece_to_position(board, move);
}
