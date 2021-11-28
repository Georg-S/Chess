#include "Chess/GameLogic.h"

inline bool is_occupied(uint32_t field)
{
	return field & field_is_occupied;
}

bool is_field_occupied(const Board& board, int x, int y)
{
	return is_occupied(board[x][y]);
}

PieceColor get_piece_color(uint32_t piece)
{
	assert(is_occupied(piece));

	if (piece & color_is_black)
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
	uint32_t val = piece & piece_mask;
	assert(val);

	return val;
}

bool is_move_valid(const Board& board, const Move& move)
{
	return true;
}

void make_move(Board& board, Move& move)
{
	uint32_t piece = board[move.fromX][move.fromY];
	assert(piece);
	board[move.fromX][move.fromY] = 0;
	board[move.toX][move.toY] = piece | moved;
}

bool has_pawn_reached_end_of_board(const Board& board)
{
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
	return false;
}

bool is_check_mate(const Board& board, PieceColor color)
{
	return false;
}

bool is_stale_mate(const Board& board, PieceColor color)
{
	return false;
}

bool direct_move_possible(const Board& board, const Move& move, int dir_x, int dir_y)
{
	if (is_field_occupied(board, move.toX, move.toY))
	{
		const auto from_color = get_piece_color(board, move.fromX, move.fromY);
		const auto to_color = get_piece_color(board, move.toX, move.toY);
		if (from_color == to_color)
			return false;
	}

	int x = move.fromX + dir_x;
	int y = move.fromY + dir_y;

	while ((x != move.toX) && (y != move.toY))
	{
		if (is_field_occupied(board, x, y))
			return false;

		x += dir_x;
		y += dir_y;
	}

	return true;
}

std::pair<int, int> get_direction(const Move& move)
{
	int dir_x = move.toX - move.fromX;
	int dir_y = move.toY - move.fromY;

	dir_x = std::max(-1, std::min(dir_x, 1));
	dir_y = std::max(-1, std::min(dir_y, 1));

	return std::pair<int, int>(dir_x, dir_y);
}

bool direct_move_possible(const Board& board, const Move& move)
{
	auto [dir_x, dir_y] = get_direction(move);

	return direct_move_possible(board, move, dir_x, dir_y);
}
