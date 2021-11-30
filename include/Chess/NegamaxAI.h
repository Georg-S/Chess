#pragma once
#include <time.h>
#include "Board.h"
#include "GameLogic.h"

class NegamaxAI
{
public:
	NegamaxAI();
	Move get_move(const Board& board, PieceColor color, int depth = 3);

private:
	Move get_random_move(const std::vector<Move>& moves);
	int evaluate_board_negamax(const Board& board, PieceColor current_player_color, int depth, int alpha, int beta);
	int static_board_evaluation(const Board& board, PieceColor current_player);
	int get_piece_value(const Board& board, PieceColor current_player, int x, int y);
	inline int get_piece_value(uint32_t piece);
	std::vector<Move> get_best_moves(std::vector<std::pair<int, Move>> moves);

	static constexpr int min_value = -100000;
	static constexpr int max_value = 100000;
};