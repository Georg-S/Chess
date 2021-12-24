#pragma once
#include "Chess/Board.h"

namespace Pawn 
{
	bool is_move_valid(const Board& board, const Move& move);
	void make_move(Board& board, const Move& move);
	bool is_en_passant_move(const Board& board, const Move& move);
}