#pragma once
#include <vector>
#include "Board.h"
#include "Utility.h"

namespace ceg
{
	struct Move
	{
		uint64_t from;
		uint64_t to;
	};

	class MoveGenerator
	{
	public:
		MoveGenerator();
		std::vector<Move> get_all_possible_moves(const BitBoard& board, bool black);

		static constexpr int arr_size = board_height * board_width;
		uint64_t vertical_mask[arr_size]{};
		uint64_t horizontal_mask[arr_size]{};
		uint64_t diagonal_up_mask[arr_size]{};
		uint64_t diagonal_down_mask[arr_size]{};

	private:
		void init();
		void init_mask(uint64_t* mask, int x_dir, int y_dir);
	};
}