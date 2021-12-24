#pragma once
#include "Chess/Board.h"

namespace Queen 
{
	bool is_move_valid(const Board& board, const Move& move);
	void make_move(Board& board, const Move& move);
}