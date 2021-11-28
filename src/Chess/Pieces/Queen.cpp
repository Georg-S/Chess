#include "Chess/Pieces/Queen.h"
#include "Chess/GameLogic.h"

bool Queen::is_move_valid(const Board& board, const Move& move)
{
    const auto [distance_x, distance_y] = get_distance(move);

    if ((abs(distance_x) == abs(distance_y)) || (distance_x == 0) || (distance_y == 0))
        return direct_move_possible(board, move);

    return false;
}
