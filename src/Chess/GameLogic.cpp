#include "Chess/GameLogic.h"

inline bool is_occupied(uint32_t field)
{
	return field & occupied_bit;
}

inline bool has_moved(uint32_t field)
{
	return field & moved_bit;
}

bool is_field_occupied(const Board& board, int x, int y)
{
	return is_occupied(board[x][y]);
}

bool has_moved(const Board& board, int x, int y)
{
	return has_moved(board[x][y]);
}

int get_en_passant_direction(const Board& board, int x, int y)
{
	if (board[x][y] & en_paasant_x_negative_bit)
		return -1;
	if (board[x][y] & en_passant_x_positive_bit)
		return 1;
	return 0;
}

PieceColor get_piece_color(uint32_t piece)
{
	assert(is_occupied(piece));

	if (piece & color_black_bit)
		return PieceColor::BLACK;
	else
		return PieceColor::WHITE;
}

PieceColor get_piece_color(const Board& board, int x, int y)
{
	return get_piece_color(board[x][y]);
}

uint32_t get_piece_type_value(uint32_t piece)
{
	assert(is_occupied(piece));
	uint32_t val = piece & piece_bit_mask;
	assert(val);

	return val;
}

bool pieces_have_different_color(const Board& board, const Move& move)
{
	assert(is_field_occupied(board, move.fromX, move.fromY));
	assert(is_field_occupied(board, move.toX, move.toY));

	const auto from_color = get_piece_color(board, move.fromX, move.fromY);
	const auto to_color = get_piece_color(board, move.toX, move.toY);

	return from_color != to_color;
}

static bool is_piece_move_valid(const Board& board, const Move& move)
{
	uint32_t piece = get_piece_type_value(board[move.fromX][move.fromY]);

	switch (piece)
	{
	case pawn_bit:
		return Pawn::is_move_valid(board, move);
		break;
	case knight_bit:
		return Knight::is_move_valid(board, move);
		break;
	case queen_bit:
		return Queen::is_move_valid(board, move);
		break;
	case king_bit:
		return King::is_move_valid(board, move);
		break;
	case bishop_bit:
		return Bishop::is_move_valid(board, move);
		break;
	case rook_bit:
		return Rook::is_move_valid(board, move);
		break;
	default:
		assert(0);
	}
	return false;
}

bool is_move_valid(const Board& board, const Move& move)
{
	if (!is_piece_move_valid(board, move))
		return false;

	PieceColor color = get_piece_color(board, move.fromX, move.fromY);
	Board board_copy = board;
	make_move(board_copy, move);

	return !is_check(board_copy, color);
}

void reset_en_passant_direction_for_color(Board& board, PieceColor color)
{
	for (int x = 0; x < board_width; x++) 
	{
		for (int y = 0; y < board_height; y++) 
		{
			if (!is_occupied(board[x][y]))
				continue;
			if (get_piece_color(board[x][y]) == color)
				board[x][y] = board[x][y] & en_passant_clear_mask;
		}
	}
}

void make_move(Board& board, const Move& move)
{
	const uint32_t piece = get_piece_type_value(board[move.fromX][move.fromY]);
	assert(piece);
	PieceColor color = get_piece_color(board, move.fromX, move.fromY);
	reset_en_passant_direction_for_color(board, color);

	switch (piece)
	{
	case pawn_bit:
		Pawn::make_move(board, move);
		break;
	case knight_bit:
		Knight::make_move(board, move);
		break;
	case queen_bit:
		Queen::make_move(board, move);
		break;
	case king_bit:
		King::make_move(board, move);
		break;
	case bishop_bit:
		Bishop::make_move(board, move);
		break;
	case rook_bit:
		Rook::make_move(board, move);
		break;
	default:
		assert(0);
	}
}

void make_move_with_automatic_promotion(Board& board, const Move& move)
{
	make_move(board, move);
	if (has_pawn_reached_end_of_board(board)) 
	{
		uint32_t color = board[move.toX][move.toY] & color_black_bit;
		board[move.toX][move.toY] = queen_bit | moved_bit | occupied_bit | color_black_bit;
	}
}

void move_piece_to_position(Board& board, const Move& move)
{
	board[move.toX][move.toY] = board[move.fromX][move.fromY] | moved_bit;
	board[move.fromX][move.fromY] = 0;
}

bool has_pawn_reached_end_of_board(const Board& board)
{
	for (int x = 0; x < board_width; x++) 
	{
		if ((board[x][0] & pawn_bit) || (board[x][board_height-1] & pawn_bit))
			return true;
	}

	return false;
}

PieceColor get_next_player(PieceColor player)
{
	assert(player != PieceColor::UNDEFINED);
	if (player == PieceColor::BLACK)
		return PieceColor::WHITE;
	else if (player == PieceColor::WHITE)
		return PieceColor::BLACK;
}

bool is_game_over(const Board& board, PieceColor color)
{
	return is_check_mate(board, color) || is_stale_mate(board, color);
}

bool is_check(const Board& board, PieceColor color)
{
	auto [king_x, king_y] = get_king_pos(board, color);
	assert(king_x != -1);

	return is_check(board, king_x, king_y);
}

bool is_check(const Board& board, int king_x, int king_y)
{
	PieceColor king_color = get_piece_color(board, king_x, king_y);

	for (int x = 0; x < board_width; x++)
	{
		for (int y = 0; y < board_height; y++)
		{
			if (!is_occupied(board[x][y]))
				continue;

			PieceColor piece_color = get_piece_color(board, x, y);
			if (piece_color == king_color)
				continue;

			if (is_piece_move_valid(board, { x, y, king_x, king_y }))
				return true;
		}
	}

	return false;
}

bool is_check_mate(const Board& board, PieceColor color)
{
	if (!is_check(board, color))
		return false;
	if (any_move_possible(board, color))
		return false;

	return true;
}

bool is_stale_mate(const Board& board, PieceColor color)
{
	if (is_check(board, color))
		return false;
	if (any_move_possible(board, color))
		return false;

	return true;
}

bool direct_move_possible(const Board& board, const Move& move, int dir_x, int dir_y)
{
	if (is_field_occupied(board, move.toX, move.toY))
	{
		if (!pieces_have_different_color(board, move))
			return false;
	}

	int x = move.fromX + dir_x;
	int y = move.fromY + dir_y;

	while ((x != move.toX) || (y != move.toY))
	{
		if (is_field_occupied(board, x, y))
			return false;

		x += dir_x;
		y += dir_y;
	}

	return true;
}

int get_x_direction(const Move& move)
{
	return std::max(-1, std::min(move.toX - move.fromX, 1));
}

int get_y_direction(const Move& move)
{
	return std::max(-1, std::min(move.toY - move.fromY, 1));
}

std::pair<int, int> get_direction(const Move& move)
{
	/*
	int dir_x = move.toX - move.fromX;
	int dir_y = move.toY - move.fromY;

	dir_x = std::max(-1, std::min(dir_x, 1));
	dir_y = std::max(-1, std::min(dir_y, 1));
	*/
	return std::pair<int, int>(get_x_direction(move), get_y_direction(move));
}

int get_x_distance(const Move& move)
{
	return move.toX - move.fromX;
}

int get_y_distance(const Move& move)
{
	return move.toY - move.fromY;
}

std::pair<int, int> get_king_pos(const Board& board, PieceColor color)
{
	for (int x = 0; x < board_width; x++)
	{
		for (int y = 0; y < board_height; y++)
		{
			if (!is_occupied(board[x][y]))
				continue;

			PieceColor piece_color = get_piece_color(board, x, y);
			if (piece_color != color)
				continue;

			if (board[x][y] & king_bit)
				return std::pair<int, int>(x, y);
		}
	}
	return std::pair<int, int>(-1, -1);
}

std::pair<int, int> get_distance(const Move& move)
{
	return std::pair<int, int>(get_x_distance(move), get_y_distance(move));
}

void get_all_possible_moves_for_piece(const Board& board, std::vector<Move>& out_vec, int x, int y)
{
	for (int board_x = 0; board_x < board_width; board_x++)
	{
		for (int board_y = 0; board_y < board_height; board_y++)
		{
			Move move = Move{ x, y, board_x, board_y };
			if (is_move_valid(board, move))
				out_vec.push_back(std::move(move));
		}
	}
}

std::vector<Move> get_all_possible_moves(const Board& board, PieceColor color)
{
	std::vector<Move> possible_moves;

	for (int from_x = 0; from_x < board_width; from_x++)
	{
		for (int from_y = 0; from_y < board_height; from_y++)
		{
			if (!is_occupied(board[from_x][from_y]))
				continue;
			PieceColor piece_color = get_piece_color(board[from_x][from_y]);
			if (piece_color != color)
				continue;

			get_all_possible_moves_for_piece(board, possible_moves, from_x, from_y);
		}
	}
	
	return possible_moves;
}

bool any_move_possible_for_piece(const Board& board, int x, int y)
{
	for (int board_x = 0; board_x < board_width; board_x++)
	{
		for (int board_y = 0; board_y < board_height; board_y++)
		{
			Move move = Move{ x, y, board_x, board_y };
			if (is_move_valid(board, move))
				return true;
		}
	}
	return false;
}

bool any_move_possible(const Board& board, PieceColor color)
{
	for (int from_x = 0; from_x < board_width; from_x++)
	{
		for (int from_y = 0; from_y < board_height; from_y++)
		{
			if (!is_occupied(board[from_x][from_y]))
				continue;
			PieceColor piece_color = get_piece_color(board[from_x][from_y]);
			if (piece_color != color)
				continue;

			if (any_move_possible_for_piece(board, from_x, from_y))
				return true;
		}
	}

	return false;
}

bool direct_move_possible(const Board& board, const Move& move)
{
	const auto [dir_x, dir_y] = get_direction(move);

	return direct_move_possible(board, move, dir_x, dir_y);
}
