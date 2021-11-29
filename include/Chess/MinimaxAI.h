#pragma once
#include "Board.h"

class MinimaxAI
{
public:
	Move get_move(const Board& board, PieceColor color);

private:
	PieceColor ai_color;
};