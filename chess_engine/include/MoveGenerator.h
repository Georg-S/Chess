#pragma once
#include <vector>
#include "Board.h"
#include "Utility.h"

namespace ceg
{
	struct Move
	{
		int from;
		int to;
	};

	class MoveGenerator
	{
	public:
		MoveGenerator();
		std::vector<Move> get_all_possible_moves(BitBoard board, bool black);
		void make_move(BitBoard& board, const Move& move);
		void make_move_with_auto_promotion(BitBoard& board, const Move& move);

		static constexpr int arr_size = board_height * board_width;
		uint64_t vertical_mask[arr_size]{};
		uint64_t horizontal_mask[arr_size]{};
		uint64_t diagonal_up_mask[arr_size]{};
		uint64_t diagonal_down_mask[arr_size]{};

		uint64_t knight_moves[arr_size]{};
		uint64_t rook_moves[arr_size]{};
		uint64_t bishop_moves[arr_size]{};
		uint64_t queen_moves[arr_size]{};
		uint64_t king_moves[arr_size]{};
		uint64_t black_pawn_normal_moves[arr_size]{};
		uint64_t black_pawn_attack_moves[arr_size]{};
		uint64_t white_pawn_normal_moves[arr_size]{};
		uint64_t white_pawn_attack_moves[arr_size]{};
	private:
		// TODO implement a more performant way, which looks up the moves.
		uint64_t get_raw_rook_moves(const BitBoard& board, int index);
		uint64_t get_raw_bishop_moves(const BitBoard& board, int index);
		uint64_t get_raw_queen_moves(const BitBoard& board, int index);

		void init();
		void init_mask(uint64_t* mask, int x_dir, int y_dir);
		void init_knight_moves();
		void init_rook_moves();
		void init_bishop_moves();
		void init_queen_moves();
		void init_king_moves();
		void init_pawn_moves();
	};
}