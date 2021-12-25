#include "MoveGenerator.h"

ceg::MoveGenerator::MoveGenerator()
{
	init();
}


uint64_t ceg::MoveGenerator::get_raw_rook_moves(const BitBoard& board)
{
	return uint64_t();
}

void ceg::MoveGenerator::init()
{
	init_mask(vertical_mask, 0, 1);
	init_mask(horizontal_mask, 1, 0);
	init_mask(diagonal_down_mask, 1, 1);
	init_mask(diagonal_up_mask, 1, -1);

	init_knight_moves();
	init_rook_moves();
	init_bishop_moves();
	init_queen_moves(); // needs to happen after rook and bishop
	init_king_moves();
	init_pawn_moves();
}

std::vector<ceg::Move> ceg::MoveGenerator::get_all_possible_moves(const BitBoard& board, bool black)
{
	std::vector<Move> result;



	return result;
}

void ceg::MoveGenerator::init_mask(uint64_t* mask, int x_dir, int y_dir)
{
	for (int i = 0; i < arr_size; i++)
	{
		const int x = i % 8;
		const int y = i / 8;

		mask[i] = set_all_bits_in_direction(x, y, x_dir, y_dir, true) | set_all_bits_in_direction(x, y, -x_dir, -y_dir, true);
	}
}

void ceg::MoveGenerator::init_knight_moves()
{
	auto get_knight_moves = [](int pos_x, int pos_y) -> uint64_t 
	{
		uint64_t result = 0;
		for (int x = -2; x < 3; x++) 
		{
			for (int y = -2; y < 3; y++) 
			{
				if (abs(x) + abs(y) != 3)
					continue;

				int new_pos_x = pos_x + x;
				int new_pos_y = pos_y + y;

				if (in_board_bounds(new_pos_x) && in_board_bounds(new_pos_y))
					set_bit(result, new_pos_x, new_pos_y);
			}
		}
		return result;
	};

	for (int i = 0; i < arr_size; i++)
	{
		const int x = i % 8;
		const int y = i / 8;
		knight_moves[i] = get_knight_moves(x, y);
	}
}

void ceg::MoveGenerator::init_rook_moves()
{
	for (int i = 0; i < arr_size; i++)
	{
		rook_moves[i] = vertical_mask[i] | horizontal_mask[i];
		clear_bit(rook_moves[i], i);
	}
}

void ceg::MoveGenerator::init_bishop_moves()
{
	for (int i = 0; i < arr_size; i++)
	{
		bishop_moves[i] = diagonal_down_mask[i] | diagonal_up_mask[i];
		clear_bit(bishop_moves[i], i);
	}
}

void ceg::MoveGenerator::init_queen_moves()
{
	for (int i = 0; i < arr_size; i++)
	{
		queen_moves[i] = bishop_moves[i] | rook_moves[i];
	}
}

void ceg::MoveGenerator::init_king_moves()
{
	auto get_king_moves = [](int pos_x, int pos_y) -> uint64_t
	{
		uint64_t result = 0;
		for (int x = -1; x <= 1; x++)
		{
			for (int y = -1; y <= 1; y++)
			{
				if (x == 0 && y == 0)
					continue;

				int new_pos_x = pos_x + x;
				int new_pos_y = pos_y + y;

				if (in_board_bounds(new_pos_x) && in_board_bounds(new_pos_y))
					set_bit(result, new_pos_x, new_pos_y);
			}
		}
		return result;
	};

	for (int i = 0; i < arr_size; i++)
	{
		const int x = i % 8;
		const int y = i / 8;

		king_moves[i] = get_king_moves(x, y);
		clear_bit(king_moves[i], x, y);
	}
}

void ceg::MoveGenerator::init_pawn_moves()
{
}
