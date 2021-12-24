#include "Chess/Pieces/Pawn.h"
#include "Chess/GameLogic.h"

static bool en_passant_possible(const Board& board, const Move& move) 
{
	const int y_distance = abs(get_y_distance(move));
	const int en_passant_direction = get_en_passant_direction(board, move.fromX, move.fromY);
	if (en_passant_direction == 0)
		return false;

	if ((move.toX == move.fromX + en_passant_direction) && (y_distance == 1))
		return true;

	return false;
}

static bool is_normal_move_possible(const Board& board, const Move& move) 
{
	const auto [x_direction, y_direction] = get_direction(move);
	const int x_distance = abs(get_x_distance(move));
	const int y_distance = abs(get_y_distance(move));

	if (x_distance == 0)
	{
		if (is_field_occupied(board, move.fromX, move.fromY + y_direction))
			return false;

		if (y_distance == 1)
			return true;

		if (y_distance == 2) 
		{
			if (has_moved(board, move.fromX, move.fromY))
				return false;

			return !is_field_occupied(board, move.toX, move.toY);
		}
	}

	if ((y_distance == 1) && is_field_occupied(board, move.toX, move.toY) && pieces_have_different_color(board, move))
		return true;

	return false;
}

static void set_en_passant_direction(const Board& board, const Move& move) 
{
	auto set_en_passant_direction = [](const Board& board, PieceColor color, int x, int y, bool x_negative)
	{
		if ((x < 0) || (x >= board_width))
			return;

		if (!(board[x][y] & pawn_bit))
			return;

		auto piece_color = get_piece_color(board, x, y);
		if (color == piece_color)
			return;

		if (x_negative)
			board[x][y] = board[x][y] | en_paasant_x_negative_bit;
		else
			board[x][y] = board[x][y] | en_passant_x_positive_bit;
	};

	int y_distance = get_y_distance(move);
	if (abs(y_distance) != 2)
		return;

	auto color = get_piece_color(board[move.toX][move.toY]);
	set_en_passant_direction(board, color, move.toX + 1, move.toY, true);
	set_en_passant_direction(board, color, move.toX - 1, move.toY, false);
}

bool Pawn::is_move_valid(const Board& board, const Move& move)
{
	const PieceColor color = get_piece_color(board, move.fromX, move.fromY);
	const auto [x_distance, y_distance] = get_distance(move);
	if (abs(x_distance) > 1)
		return false;

	if ((y_distance == 0) || abs(y_distance) > 2)
		return false;
	
	if ((y_distance > 0) && color != PieceColor::BLACK)
		return false;

	if ((y_distance < 0) && color != PieceColor::WHITE)
		return false;

	return is_normal_move_possible(board, move) || en_passant_possible(board, move);
}

void Pawn::make_move(Board& board, const Move& move)
{
	if (is_en_passant_move(board, move)) 
	{
		board[move.toX][move.toY] = board[move.fromX][move.fromY] | moved_bit;
		board[move.fromX][move.fromY] = 0;
		board[move.toX][move.fromY] = 0;
	}
	else 
	{
		move_piece_to_position(board, move);
		set_en_passant_direction(board, move);
	}
}

bool Pawn::is_en_passant_move(const Board& board,const Move& move)
{
	auto [distance_x, distance_y] = get_distance(move);

	if ((abs(distance_x) == 1) && (abs(distance_y) == 1) && !is_field_occupied(board, move.toX, move.toY))
		return true;

	return false;
}
