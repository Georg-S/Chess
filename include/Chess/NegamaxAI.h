#pragma once
#include <time.h>
#include <thread>
#include <mutex>
#include <iostream>
#include "Board.h"
#include "GameLogic.h"

class NegamaxAI
{
public:
	NegamaxAI();
	Move get_move(const Board& board, PieceColor color, int depth = 4);

private:
	std::vector<std::pair<int, Move>> get_evaluated_moves(const Board& board, PieceColor color, int depth);
	std::vector<std::pair<int, Move>> get_evaluated_moves_multi_threaded(const Board& board, PieceColor color, int depth);
	void eval_multi_threaded(const Board& board, PieceColor color, const std::vector<Move>& possible_moves, int depth);
	Move get_random_move(const std::vector<Move>& moves);
	Move get_random_move(const std::vector<std::pair<int, Move>>& moves);
	int evaluate_board_negamax(const Board& board, PieceColor current_player_color, int depth, int alpha, int beta);
	int static_board_evaluation(const Board& board, PieceColor current_player);
	int get_piece_value(const Board& board, PieceColor current_player, int x, int y);
	inline int get_piece_value(uint32_t piece);
	std::vector<Move> get_best_moves(std::vector<std::pair<int, Move>> moves);

	std::vector<std::pair<int, Move>> evaluated_moves;
	std::mutex m_mutex;
	int current_index = 0;
	static constexpr int min_value = -100000;
	static constexpr int max_value = 100000;
};