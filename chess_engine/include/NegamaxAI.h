#pragma once
#include <time.h>
#include <thread>
#include <mutex>
#include <iostream>
#include <random>
#include "RNG.h"
#include "PieceSquareTable.h"
#include "BitBoard.h"
#include "MoveGenerator.h"

namespace ceg
{

	struct TTEntry
	{
		std::mutex mut;
		enum class type { EXACT, UPPER, LOWER } type;
		uint64_t hash = 0;
		int value = 0;
		int depth = 0;
		ceg::InternalMove best_move;
	};

	struct EvalMove
	{
		ceg::InternalMove move;
		int value;
	};

	inline bool operator<(const EvalMove& rhs, const EvalMove& lhs)
	{
		return rhs.value < lhs.value;
	}

	inline bool operator>(const EvalMove& rhs, const EvalMove& lhs)
	{
		return rhs.value > lhs.value;
	}

	// Most Valuable Victim, Least Valuable Attacker
	constexpr int MVV_LVA[7][7]
	{
		{0, 0, 0, 0, 0, 0, 0} ,       // Victim: King, Attacker: King, Queen, Rook, Bishop, Knight, Pawn, None
		{50, 51, 52, 53, 54, 55, 0}, //  Victim: Queen, King, Attacker: King, Queen, Rook, Bishop, Knight, Pawn, None
		{40, 41, 42, 43, 44, 45, 0}, //  Victim: Rook, King, Attacker: King, Queen, Rook, Bishop, Knight, Pawn, None
		{30, 31, 32, 33, 34, 35, 0}, //  Victim: Bishop, King, Attacker: King, Queen, Rook, Bishop, Knight, Pawn, None
		{20, 21, 22, 23, 24, 25, 0}, //  Victim: Knight, King, Attacker: King, Queen, Rook, Bishop, Knight, Pawn, None
		{10, 11, 12, 13, 14, 15, 0 }, //  Victim: Pawn, King, Attacker: King, Queen, Rook, Bishop, Knight, Pawn, None
		{0, 0, 0, 0, 0, 0, 0},       //  Victim: None, King, Attacker: King, Queen, Rook, Bishop, Knight, Pawn, None
	};

	class NegamaxAI
	{
	public:
		NegamaxAI();
		NegamaxAI(const NegamaxAI&) = delete;
		~NegamaxAI();
		ceg::InternalMove get_move(const ceg::BitBoard& board, bool color_is_black, int depth = 5);

	private:
		ceg::InternalMove iterative_deepening(const ceg::BitBoard& board, bool color_is_black, int max_depth);
		void init_hashing_table();
		uint64_t hash_board(const ceg::BitBoard& board, bool color_is_black) const;
		std::vector<EvalMove> get_evaluated_moves(const ceg::BitBoard& board, bool color_is_black, int depth);
		std::vector<EvalMove> get_evaluated_moves(const ceg::BitBoard& board, bool color_is_black, int depth, const std::vector<ceg::InternalMove>& possible_moves);
		std::vector<EvalMove> get_evaluated_moves_multi_threaded(const ceg::BitBoard& board, bool color_is_black, int depth);
		void eval_multi_threaded(const ceg::BitBoard& board, bool color_is_black, const std::vector<ceg::InternalMove>& possible_moves, int depth);
		ceg::InternalMove get_random_move(const std::vector<ceg::InternalMove>& moves);
		ceg::InternalMove get_random_move(const std::vector<std::pair<int, ceg::InternalMove>>& moves);
		std::vector<ceg::InternalMove> generate_sorted_possible_moves(const ceg::BitBoard& board, bool color_is_black, const ceg::InternalMove& tt_move);
		int evaluate_board_negamax(const ceg::BitBoard& board, bool color_is_black, int depth, int alpha, int beta);
		int static_board_evaluation(const ceg::BitBoard& board, bool current_player_black);
		int get_piece_value(const ceg::BitBoard& board, bool current_player_black, int x, int y);
		int get_piece_position_value(uint32_t piece, bool color_is_black, int x, int y);
		inline int get_raw_piece_value(uint32_t piece);
		std::vector<ceg::InternalMove> get_best_moves(std::vector<EvalMove> moves);

		std::vector<EvalMove> evaluated_moves;
		std::mutex m_mutex;
		int current_index = 0;
		static constexpr int min_value = -10000000;
		static constexpr int max_value = 10000000;
		uint64_t hashing_table[8][8][12];
		static constexpr int max_tt_entries = 50000;
		TTEntry* tt_table;
		ceg::RNG rng;
		std::unique_ptr<MoveGenerator> move_generator = nullptr;
	};
}