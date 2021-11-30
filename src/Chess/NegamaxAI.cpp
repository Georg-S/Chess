#include "Chess/NegamaxAI.h"

NegamaxAI::NegamaxAI()
{
	srand(time(NULL));
}

Move NegamaxAI::get_move(const Board& board, PieceColor color)
{
	std::vector<std::pair<int, Move>> evaluated_moves;
	auto possible_moves = get_all_possible_moves(board, color);
	int alpha = min_value;
	int beta = max_value;
	for (const auto& move : possible_moves)
	{
		Board copy_board = board;
		make_move_with_automatic_promotion(copy_board, move);

		int val = evaluate_board_negamax(copy_board, get_next_player(color), 3, -beta, -alpha);
		alpha = std::max(alpha, val);
		evaluated_moves.push_back({ val, move });
	}
	auto best_moves = get_best_moves(evaluated_moves);

	return get_random_move(best_moves);
}

Move NegamaxAI::get_random_move(const std::vector<Move>& moves)
{
	assert(moves.size());
	if (moves.size() == 0)
		return Move();

	return moves[rand() % moves.size()];
}

int NegamaxAI::evaluate_board_negamax(const Board& board, PieceColor current_player_color, int depth, int alpha, int beta)
{
	const bool no_move_possible = !any_move_possible(board, current_player_color);
	const bool check = is_check(board, current_player_color);
	if (check && no_move_possible)
		return -(min_value - depth);
	if (!check && no_move_possible)
		return 0;

	if (depth == 0)
		return -static_board_evaluation(board, current_player_color);

	auto possible_moves = get_all_possible_moves(board, current_player_color);
	int move_value = -20000;
	for (const auto& move : possible_moves)
	{
		Board copy_board = board;
		make_move_with_automatic_promotion(copy_board, move);
		move_value = std::max(move_value, evaluate_board_negamax(copy_board, get_next_player(current_player_color), depth - 1, -beta, -alpha));
		alpha = std::max(alpha, move_value);
		if (alpha >= beta)
			break;
	}

	return -move_value;
}

int NegamaxAI::static_board_evaluation(const Board& board, PieceColor current_player)
{
	int value = 0;
	for (int x = 0; x < board_width; x++)
	{
		for (int y = 0; y < board_height; y++) 
		{
			if (!is_field_occupied(board, x, y))
				continue;
			value += get_piece_value(board, current_player, x, y);
		}
	}
	return value;
}

int NegamaxAI::get_piece_value(const Board& board, PieceColor current_player, int x, int y)
{
	PieceColor piece_color = get_piece_color(board, x, y);
	int piece_value = get_piece_value(board[x][y]);
	if (piece_color == current_player)
		return piece_value;

	return -piece_value;
}

inline int NegamaxAI::get_piece_value(uint32_t piece)
{
	const uint32_t piece_type = get_piece_type_value(piece);
	switch (piece_type)
	{
	case pawn_bit:		return 1;
	case knight_bit:	return 3;
	case bishop_bit:	return 3;
	case rook_bit:		return 5;
	case queen_bit:		return 9;
	case king_bit:		return 100;
	default:			assert(0);
	}
	return 0;
}

std::vector<Move> NegamaxAI::get_best_moves(std::vector<std::pair<int, Move>> moves)
{
	std::vector<Move> best_moves;
	assert(moves.size());
	if (moves.size() == 0)
		return best_moves;

	auto compare = [](std::pair<int, Move> p1, std::pair<int, Move> p2)
	{
		return p1.first < p2.first;
	};

	auto max_element = std::max_element(moves.begin(), moves.end(), compare);

	int highest_value = (*(max_element)).first;
	for (const auto& eval_move : moves) 
	{
		if (eval_move.first == highest_value)
			best_moves.push_back(eval_move.second);
	}

	return best_moves;
}
