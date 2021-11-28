#include "Chess/Pieces/Bishop.h"
#include "Chess/GameLogic.h"

bool Bishop::is_move_valid(const Board& board, const Move& move)
{
	auto [dir_x, dir_y] = get_direction(move);

	if ((abs(dir_x) != 1) || (abs(dir_y) != 1))
		return false;

	return direct_move_possible(board, move, dir_x, dir_y);
}

void Bishop::make_move(Board& board, const Move& move)
{
}
