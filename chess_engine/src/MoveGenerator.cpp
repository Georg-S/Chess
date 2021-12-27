#include "MoveGenerator.h"

ceg::MoveGenerator::MoveGenerator()
{
	init();
}


uint64_t ceg::MoveGenerator::get_raw_rook_moves(const BitBoard& board, int index)
{
	auto result = set_all_bits_in_direction_until_occupied(index, 1, 0, board.occupied);
	result |= set_all_bits_in_direction_until_occupied(index, -1, 0, board.occupied);
	result |= set_all_bits_in_direction_until_occupied(index, 0, 1, board.occupied);
	result |= set_all_bits_in_direction_until_occupied(index, 0, -1, board.occupied);

	return result;
}

uint64_t ceg::MoveGenerator::get_raw_bishop_moves(const BitBoard& board, int index)
{
	auto result = set_all_bits_in_direction_until_occupied(index, 1, 1, board.occupied);
	result |= set_all_bits_in_direction_until_occupied(index, -1, -1, board.occupied);
	result |= set_all_bits_in_direction_until_occupied(index, 1, -1, board.occupied);
	result |= set_all_bits_in_direction_until_occupied(index, -1, 1, board.occupied);

	return result;
}

uint64_t ceg::MoveGenerator::get_raw_queen_moves(const BitBoard& board, int index)
{
	return get_raw_rook_moves(board, index) | get_raw_bishop_moves(board, index);
}

void ceg::MoveGenerator::init()
{
	init_mask(vertical_mask, 0, 1);
	init_mask(horizontal_mask, 1, 0);
	init_mask(diagonal_down_mask, 1, 1);
	init_mask(diagonal_up_mask, 1, -1);
	combine_two_masks(rook_mask, horizontal_mask, vertical_mask);
	combine_two_masks(diagonal_mask, diagonal_up_mask, diagonal_down_mask);

	init_knight_moves();
	init_rook_moves();
	init_bishop_moves();
	init_queen_moves(); // needs to happen after rook and bishop
	init_king_moves();
	init_pawn_moves();
}

void ceg::MoveGenerator::combine_two_masks(uint64_t* dest, uint64_t* source_1, uint64_t* source_2, int size)
{
	for (int i = 0; i < size; i++) 
		dest[i] = source_1[i] | source_2[i];
}

std::vector<ceg::Move> ceg::MoveGenerator::get_all_possible_moves(BitBoard board, bool black)
{
	auto push_all_moves = [](std::vector<Move>& dest, int from_index, uint64_t moves) 
	{
		while (moves != 0)
		{
			int to_index = get_bit_index_lsb(moves);
			dest.push_back(Move{ from_index, to_index });
			reset_lsb(moves);
		}
	};

	std::vector<Move> result;

	if (black) 
	{
		auto black_occupied_mask = ~board.black_pieces.occupied;

		while (board.black_pieces.bishops != 0) 
		{
			int from_index = get_bit_index_lsb(board.black_pieces.bishops);
			auto bishop_moves = get_raw_bishop_moves(board, from_index) & black_occupied_mask;
			reset_lsb(board.black_pieces.bishops);
			push_all_moves(result, from_index, bishop_moves);
		}

		while (board.black_pieces.king != 0)
		{
			int from_index = get_bit_index_lsb(board.black_pieces.king);
			auto moves = king_moves[from_index] & black_occupied_mask;
			reset_lsb(board.black_pieces.king);
			push_all_moves(result, from_index, moves);
		}

		while (board.black_pieces.knights != 0)
		{
			int from_index = get_bit_index_lsb(board.black_pieces.knights);
			auto moves = knight_moves[from_index] & black_occupied_mask;
			reset_lsb(board.black_pieces.knights);
			push_all_moves(result, from_index, moves);
		}

		while (board.black_pieces.pawns != 0)
		{
			int from_index = get_bit_index_lsb(board.black_pieces.pawns);
			auto moves = black_pawn_normal_moves[from_index] & black_occupied_mask;
			reset_lsb(board.black_pieces.pawns);
			push_all_moves(result, from_index, moves);
		}

		while (board.black_pieces.queens != 0)
		{
			int from_index = get_bit_index_lsb(board.black_pieces.queens);
			auto moves = get_raw_queen_moves(board, from_index) & black_occupied_mask;
			reset_lsb(board.black_pieces.queens);
			push_all_moves(result, from_index, moves);
		}

		while (board.black_pieces.rooks != 0)
		{
			int from_index = get_bit_index_lsb(board.black_pieces.rooks);
			auto moves = get_raw_rook_moves(board, from_index) & black_occupied_mask;
			reset_lsb(board.black_pieces.rooks);
			push_all_moves(result, from_index, moves);
		}
	}
	else 
	{
		auto white_occupied_mask = ~board.white_pieces.occupied;

		while (board.white_pieces.bishops != 0)
		{
			int from_index = get_bit_index_lsb(board.white_pieces.bishops);
			auto bishop_moves = get_raw_bishop_moves(board, from_index) & white_occupied_mask;
			reset_lsb(board.white_pieces.bishops);
			push_all_moves(result, from_index, bishop_moves);
		}

		while (board.white_pieces.king != 0)
		{
			int from_index = get_bit_index_lsb(board.white_pieces.king);
			auto moves = king_moves[from_index] & white_occupied_mask;
			reset_lsb(board.white_pieces.king);
			push_all_moves(result, from_index, moves);
		}

		while (board.white_pieces.knights != 0)
		{
			int from_index = get_bit_index_lsb(board.white_pieces.knights);
			auto moves = knight_moves[from_index] & white_occupied_mask;
			reset_lsb(board.white_pieces.knights);
			push_all_moves(result, from_index, moves);
		}

		while (board.white_pieces.pawns != 0)
		{
			int from_index = get_bit_index_lsb(board.white_pieces.pawns);
			auto moves = white_pawn_normal_moves[from_index] & white_occupied_mask;
			reset_lsb(board.white_pieces.pawns);
			push_all_moves(result, from_index, moves);
		}

		while (board.white_pieces.queens != 0)
		{
			int from_index = get_bit_index_lsb(board.white_pieces.queens);
			auto moves = get_raw_queen_moves(board, from_index) & white_occupied_mask;
			reset_lsb(board.white_pieces.queens);
			push_all_moves(result, from_index, moves);
		}

		while (board.white_pieces.rooks != 0)
		{
			int from_index = get_bit_index_lsb(board.white_pieces.rooks);
			auto moves = get_raw_rook_moves(board, from_index) & white_occupied_mask;
			reset_lsb(board.white_pieces.rooks);
			push_all_moves(result, from_index, moves);
		}
	}



	return result;
}

void ceg::MoveGenerator::make_move(BitBoard& board, const Move& move)
{
	bool move_made_by_black = false;
	if (is_bit_set(board.black_pieces.occupied, move.from))
		move_made_by_black = true;

	uint64_t* arr = board.get_ptr_to_piece(move_made_by_black, move.from);
	clear_bit(*arr, move.from);
	set_bit(*arr, move.to);

	//		const uint64_t invert_to = ~(move.to);
	if (move_made_by_black)
	{
		set_bit(board.black_pieces.occupied, move.to);

		if (is_bit_set(board.white_pieces.occupied, move.to))
			board.clear_bit_for_color(false, move.to);
	}
	else
	{
		set_bit(board.white_pieces.occupied, move.to);

		if (is_bit_set(board.black_pieces.occupied, move.to))
			board.clear_bit_for_color(true, move.to);
	}

	board.occupied = board.white_pieces.occupied | board.black_pieces.occupied;

	// TODO handle castling and en_passant
}

void ceg::MoveGenerator::make_move_with_auto_promotion(BitBoard& board, const Move& move)
{
	// TODO fully implement
	make_move(board, move);
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
	auto get_attack_move = [](int pos_x, int pos_y, int x, int y) ->uint64_t
	{
		pos_x += x;
		pos_y += y;

		uint64_t res = 0;
		if (ceg::in_board_bounds(pos_x) && ceg::in_board_bounds(pos_y))
			set_bit(res, pos_x, pos_y);

		return res;
	};


	for (int i = 8; i < 56; i++)
	{
		int x = i % 8;
		int y = i / 8;

		black_pawn_attack_moves[i] = get_attack_move(x, y, 1, 1) | get_attack_move(x, y, -1, 1);

		if (y == 1)
		{
			uint64_t normal_moves = 0;
			set_bit(normal_moves, x, y + 1);
			set_bit(normal_moves, x, y + 2);

			black_pawn_normal_moves[i] = normal_moves;
		}
		else
		{
			uint64_t res = 0;
			set_bit(res, x, y + 1);
			black_pawn_normal_moves[i] = res;
		}
	}

	for (int i = 8; i < 56; i++)
	{
		int x = i % 8;
		int y = i / 8;

		white_pawn_attack_moves[i] = get_attack_move(x, y, 1, -1) | get_attack_move(x, y, -1, -1);

		if (y == 6)
		{
			uint64_t normal_moves = 0;
			set_bit(normal_moves, x, y - 1);
			set_bit(normal_moves, x, y - 2);

			white_pawn_normal_moves[i] = normal_moves;
		}
		else
		{
			uint64_t res = 0;
			set_bit(res, x, y - 1);
			white_pawn_normal_moves[i] = res;
		}
	}
}
