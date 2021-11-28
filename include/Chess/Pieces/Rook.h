#pragma once
#include "Chess/Board.h"

namespace Rook 
{
	bool is_move_valid(const Board& board, const Move& move);
	void make_move(Board& board, const Move& move);
}