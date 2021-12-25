#include "MoveGenerator.h"

ceg::MoveGenerator::MoveGenerator()
{
	init();
}


void ceg::MoveGenerator::init()
{
	init_mask(vertical_mask, 0, 1);
	init_mask(horizontal_mask, 1, 0);
	init_mask(diagonal_down_mask, 1, 1);
	init_mask(diagonal_up_mask, 1, -1);
}

std::vector<ceg::Move> ceg::MoveGenerator::get_all_possible_moves(const BitBoard& board, bool black)
{
	std::vector<Move> result;

	auto knights = black ? board.black_knights : board.white_knights;

	int raw_knight_moves[64];
//	get_raw_knight_moves(raw_knight_moves);


	return result;
}

void ceg::MoveGenerator::init_mask(uint64_t* mask, int x_dir, int y_dir)
{
	for (int i = 0; i < 64; i++)
	{
		const int x = i % 8;
		const int y = i / 8;

		mask[i] = set_all_bits_in_direction(x, y, x_dir, y_dir, true) | set_all_bits_in_direction(x, y, -x_dir, -y_dir, true);
	}
}

static void get_raw_knight_moves(int* arr, int index)
{
}