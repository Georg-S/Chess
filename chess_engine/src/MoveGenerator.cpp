#include "MoveGenerator.h"

ceg::MoveGenerator::MoveGenerator()
{
	init();
}

void ceg::MoveGenerator::get_check_info(Pieces* player, Pieces* other, const BitBoard& board, CheckInfo* out_check_info, const uint64_t* pawn_attack_moves)
{
	int other_king_index = get_bit_index_lsb(other->king);
	uint64_t occupied = board.occupied;
	occupied &= reset_index_mask[other_king_index];

	const uint64_t playing_occupied_mask = ~(player->occupied);
	while (player->rooks != 0)
	{
		int from_index = get_bit_index_lsb(player->rooks);
		uint64_t moves = get_raw_rook_moves(from_index, occupied);
		reset_lsb(player->rooks);

		out_check_info->attacked_fields |= moves;

		if (moves & other->king) 
			out_check_info->check_counter++;
	}

	while (player->queens != 0)
	{
		int from_index = get_bit_index_lsb(player->queens);
		uint64_t moves = get_raw_queen_moves(from_index, occupied);
		reset_lsb(player->queens);

		out_check_info->attacked_fields |= moves;

		if (moves & other->king)
			out_check_info->check_counter++;
	}

	while (player->bishops != 0)
	{
		int from_index = get_bit_index_lsb(player->bishops);
		uint64_t moves = get_raw_bishop_moves(from_index, occupied);
		reset_lsb(player->bishops);

		out_check_info->attacked_fields |= moves;

		if (moves & other->king)
			out_check_info->check_counter++;
	}

	while (player->king != 0)
	{
		int from_index = get_bit_index_lsb(player->king);
		auto moves = king_moves[from_index];
		reset_lsb(player->king);

		out_check_info->attacked_fields |= moves;
	}

	while (player->knights != 0)
	{
		int from_index = get_bit_index_lsb(player->knights);
		auto moves = knight_moves[from_index];
		reset_lsb(player->knights);

		out_check_info->attacked_fields |= moves;

		if (moves & other->king)
			out_check_info->check_counter++;
	}

	while (player->pawns != 0)
	{
		// TODO en passant
		int from_index = get_bit_index_lsb(player->pawns);
		auto attack_moves = pawn_attack_moves[from_index];
		reset_lsb(player->pawns);

		out_check_info->attacked_fields |= attack_moves;

		if (attack_moves & other->king)
			out_check_info->check_counter++;
	}
}

uint64_t ceg::MoveGenerator::get_raw_rook_moves(int index, uint64_t occupied)
{
	uint64_t horiz = occupied & horizontal_mask_without_index[index];
	uint64_t vert = occupied & vertical_mask_without_index[index];

	return horizontal_with_occupied[index][horiz] | vertical_with_occupied[index][vert];
}

uint64_t ceg::MoveGenerator::get_raw_bishop_moves(int index, uint64_t occupied)
{
	uint64_t up = occupied & diagonal_up_mask_without_index[index];
	uint64_t down = occupied & diagonal_down_mask_without_index[index];

	return diagonal_up_with_occupied[index][up] | diagonal_down_with_occupied[index][down];
}

uint64_t ceg::MoveGenerator::get_raw_queen_moves(int index, uint64_t occupied)
{
	return get_raw_rook_moves(index, occupied) | get_raw_bishop_moves(index, occupied);
}

void ceg::MoveGenerator::init()
{
	init_reset_index_mask();
	init_mask(vertical_mask, 0, 1, true);
	init_mask(horizontal_mask, 1, 0, true);
	init_mask(diagonal_down_mask, 1, 1, true);
	init_mask(diagonal_up_mask, 1, -1, true);
	init_mask(vertical_mask_without_index, 0, 1, false);
	init_mask(horizontal_mask_without_index, 1, 0, false);
	init_mask(diagonal_up_mask_without_index, 1, -1, false);
	init_mask(diagonal_down_mask_without_index, 1, 1, false);
	combine_two_masks(rook_mask, horizontal_mask, vertical_mask);
	combine_two_masks(diagonal_mask, diagonal_up_mask, diagonal_down_mask);

	init_knight_moves();
	init_rook_moves();
	init_bishop_moves();
	init_queen_moves(); // needs to happen after rook and bishop
	init_king_moves();
	init_pawn_moves();

	init_mask_with_occupied(diagonal_up_with_occupied, diagonal_up_mask, 1, -1);
	init_mask_with_occupied(diagonal_down_with_occupied, diagonal_down_mask, 1, 1);
	init_mask_with_occupied(vertical_with_occupied, vertical_mask, 0, 1);
	init_mask_with_occupied(horizontal_with_occupied, horizontal_mask, 1, 0);
}

void ceg::MoveGenerator::init_reset_index_mask()
{
	for (int i = 0; i < 64; i++) 
	{
		uint64_t val = 0;
		val = ~val;
		clear_bit(val, i);
		reset_index_mask[i] = val;
	}
}

void ceg::MoveGenerator::combine_two_masks(uint64_t* dest, uint64_t* source_1, uint64_t* source_2, int size)
{
	for (int i = 0; i < size; i++) 
		dest[i] = source_1[i] | source_2[i];
}

void ceg::MoveGenerator::init_mask(uint64_t* mask, int x_dir, int y_dir, bool set_inital_index)
{
	for (int i = 0; i < arr_size; i++)
	{
		const int x = i % 8;
		const int y = i / 8;

		mask[i] = set_all_bits_in_direction(x, y, x_dir, y_dir, set_inital_index) | set_all_bits_in_direction(x, y, -x_dir, -y_dir, set_inital_index);
	}
}

std::vector<ceg::Move> ceg::MoveGenerator::get_all_possible_moves(BitBoard board, bool black)
{
	Pieces black_pieces = board.black_pieces;
	Pieces white_pieces = board.white_pieces;

	if (black) 
	{
		return get_all_possible_moves(&black_pieces, &white_pieces, board, black_pawn_normal_moves, black_pawn_attack_moves, true);
	}
	else 
	{
		return get_all_possible_moves(&white_pieces, &black_pieces, board, white_pawn_normal_moves, white_pawn_attack_moves, false);
	}
}

std::vector<ceg::Move> ceg::MoveGenerator::get_all_possible_moves(Pieces* playing, ceg::Pieces* other, 
	const BitBoard& board, uint64_t* pawn_normal_moves, uint64_t* pawn_attack_moves, bool black)
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
	auto playing_occupied_mask = ~(playing->occupied);

	ceg::Pieces cop_other = *other;
	auto other_pawn_attack_moves = black ? white_pawn_attack_moves : black_pawn_attack_moves;

	CheckInfo info = CheckInfo();
	get_check_info(&cop_other, playing, board, &info, other_pawn_attack_moves);
	const uint64_t attacked_fields_mask = ~(info.attacked_fields);

	while (playing->king != 0)
	{
		int from_index = get_bit_index_lsb(playing->king);
		auto moves = king_moves[from_index] & playing_occupied_mask & attacked_fields_mask;
		reset_lsb(playing->king);
		push_all_moves(result, from_index, moves);
	}

	if (info.check_counter >= 2)
		return result;

	while (playing->bishops != 0)
	{
		int from_index = get_bit_index_lsb(playing->bishops);
		auto bishop_moves = get_raw_bishop_moves(from_index, board.occupied) & playing_occupied_mask;
		reset_lsb(playing->bishops);
		push_all_moves(result, from_index, bishop_moves);
	}

	while (playing->knights != 0)
	{
		int from_index = get_bit_index_lsb(playing->knights);
		auto moves = knight_moves[from_index] & playing_occupied_mask;
		reset_lsb(playing->knights);
		push_all_moves(result, from_index, moves);
	}

	while (playing->pawns != 0)
	{
		// TODO en passant
		int from_index = get_bit_index_lsb(playing->pawns);
		uint64_t normal_moves = 0;
		int moving = black ? 8 : -8;

		if (!is_bit_set(board.occupied, from_index + moving))
			normal_moves = pawn_normal_moves[from_index] & ~board.occupied;
		auto attack_moves = pawn_attack_moves[from_index] & other->occupied;
		auto moves = normal_moves | attack_moves;
		reset_lsb(playing->pawns);
		push_all_moves(result, from_index, moves);
	}

	while (playing->queens != 0)
	{
		int from_index = get_bit_index_lsb(playing->queens);
		auto moves = get_raw_queen_moves(from_index, board.occupied) & playing_occupied_mask;
		reset_lsb(playing->queens);
		push_all_moves(result, from_index, moves);
	}

	while (playing->rooks != 0)
	{
		int from_index = get_bit_index_lsb(playing->rooks);
		auto moves = get_raw_rook_moves(from_index, board.occupied) & playing_occupied_mask;
		reset_lsb(playing->rooks);
		push_all_moves(result, from_index, moves);
	}

	return result;
}

void ceg::MoveGenerator::make_move(BitBoard& board, const Move& move)
{
	bool move_made_by_black = false;
	if (is_bit_set(board.black_pieces.occupied, move.from))
		move_made_by_black = true;

	make_move(board, move, move_made_by_black);
}

void ceg::MoveGenerator::make_move(BitBoard& board, const Move& move, bool black)
{
	Pieces* pieces = black ? &(board.black_pieces) : &(board.white_pieces);
	Pieces* other = black ? &(board.white_pieces) : &(board.black_pieces);
	uint64_t* arr = board.get_ptr_to_piece(pieces, move.from);

	clear_bit(*arr, move.from);
	set_bit(*arr, move.to);

	clear_bit(pieces->occupied, move.from);
	set_bit(pieces->occupied, move.to);

	if (is_bit_set(other->occupied, move.to))
		board.clear_bit_for_pieces(other, move.to);

	board.update_occupied();

	// TODO handle castling and en_passant
}

void ceg::MoveGenerator::make_move_with_auto_promotion(BitBoard& board, const Move& move)
{
	// TODO fully implement
	make_move(board, move);
}

void ceg::MoveGenerator::init_mask_with_occupied(std::unordered_map<uint64_t, uint64_t>* arr, uint64_t* mask, int x_dir, int y_dir)
{
	for (int bit_index = 0; bit_index < 64; bit_index++) 
	{
		auto num = mask[bit_index];
		clear_bit(num, bit_index);

		auto possible_occupied = ceg::get_every_bit_combination(ceg::get_bit_indices(num));
		for (auto& occ : possible_occupied)
		{
			uint64_t res = 0;
			res |= ceg::set_all_bits_in_direction_until_occupied(bit_index, x_dir, y_dir, occ);
			res |= ceg::set_all_bits_in_direction_until_occupied(bit_index, -x_dir, -y_dir, occ);

			arr[bit_index][occ] = res;
		}
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

/*
void ceg::MoveGenerator::init_rook_moves_with_occupied(int index)
{
	auto num = rook_mask[index];
	clear_bit(num, index);

	auto possible_occupied = ceg::get_every_bit_combination(ceg::get_bit_indices(num));
	for (auto& occ : possible_occupied)
	{
		uint64_t res = 0;
		res |= ceg::set_all_bits_in_direction_until_occupied(index, 1, 0, occ);
		res |= ceg::set_all_bits_in_direction_until_occupied(index, -1, 0, occ);
		res |= ceg::set_all_bits_in_direction_until_occupied(index, 0, 1, occ);
		res |= ceg::set_all_bits_in_direction_until_occupied(index, 0, -1, occ);

		rook_moves_with_occupied[index][occ] = res;
	}


}
*/
