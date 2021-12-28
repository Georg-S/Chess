#pragma once
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "BitBoard.h"
#include "Utility.h"

namespace ceg
{
	struct Move
	{
		int from;
		int to;
	};

	struct CheckInfo 
	{
		CheckInfo() 
		{
			uint64_t zero = 0;
			std::fill_n(pin_mask, 64, ~zero);
		}

		int check_counter = 0;
		uint64_t attacked_fields = 0;
		uint64_t pin_mask[64];
		uint64_t check_mask = ~uint64_t(0);
	};

	class MoveGenerator
	{
	public:
		MoveGenerator();
		void get_check_info(Pieces* player, Pieces* other, const BitBoard& board, CheckInfo* out_check_info, const uint64_t* pawn_attack_moves);
		std::vector<Move> get_all_possible_moves(BitBoard board, bool black);
		std::vector<Move> get_all_possible_moves(Pieces* playing, ceg::Pieces* other, const BitBoard& board,
			uint64_t* pawn_normal_moves, uint64_t* pawn_attack_moves, bool black);
		void make_move(BitBoard& board, const Move& move);
		void make_move(BitBoard& board, const Move& move, bool black);
		void make_move_with_auto_promotion(BitBoard& board, const Move& move);

		static constexpr int arr_size = board_height * board_width;
		uint64_t vertical_mask[arr_size]{};
		uint64_t vertical_mask_without_index[arr_size]{};
		uint64_t horizontal_mask[arr_size]{};
		uint64_t horizontal_mask_without_index[arr_size]{};
		uint64_t diagonal_up_mask[arr_size]{};
		uint64_t diagonal_up_mask_without_index[arr_size]{};
		uint64_t diagonal_down_mask[arr_size]{};
		uint64_t diagonal_down_mask_without_index[arr_size]{};
		uint64_t diagonal_mask[arr_size]{};
		uint64_t reset_index_mask[arr_size]{};

		uint64_t rook_mask[arr_size]{};
		std::unordered_map<uint64_t, uint64_t> horizontal_with_occupied[arr_size]{};
		std::unordered_map<uint64_t, uint64_t> vertical_with_occupied[arr_size]{};
		std::unordered_map<uint64_t, uint64_t> diagonal_up_with_occupied[arr_size]{};
		std::unordered_map<uint64_t, uint64_t> diagonal_down_with_occupied[arr_size]{};

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
		uint64_t get_raw_rook_moves(int index, uint64_t occupied);
		uint64_t get_raw_bishop_moves(int index, uint64_t occupied);
		uint64_t get_raw_queen_moves(int index, uint64_t occupied);
		uint64_t get_vertical_moves(int index, uint64_t occupied);
		uint64_t get_horizontal_moves(int index, uint64_t occupied);
		uint64_t get_diagonal_up_moves(int index, uint64_t occupied);
		uint64_t get_diagonal_down_moves(int index, uint64_t occupied);

		void init();
		void init_reset_index_mask();
		void combine_two_masks(uint64_t* dest, uint64_t* source_1, uint64_t* source_2, int size = arr_size);
		void init_mask(uint64_t* mask, int x_dir, int y_dir, bool set_inital_index);
		void init_mask_with_occupied(std::unordered_map<uint64_t, uint64_t>* arr, uint64_t* mask, int x_dir, int y_dir);
		void init_knight_moves();
		void init_rook_moves();
		void init_bishop_moves();
		void init_queen_moves();
		void init_king_moves();
		void init_pawn_moves();
	};
}