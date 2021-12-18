#include "Chess/NegamaxAI.h"

NegamaxAI::NegamaxAI()
{
	srand(time(NULL));
	init_hashing_table();
	tt_table = new TTEntry[max_tt_entries];
}

NegamaxAI::~NegamaxAI()
{
	delete[] tt_table;
}

Move NegamaxAI::get_move(const Board& board, PieceColor color, int depth)
{
	/*
	auto evaluated_moves = get_evaluated_moves(board, color, depth);
	auto evaluated_moves = get_evaluated_moves_multi_threaded(board, color, depth);
	auto best_moves = get_best_moves(evaluated_moves);

	return get_random_move(best_moves);
	*/
	return iterative_deepening(board, color, depth);
}

Move NegamaxAI::iterative_deepening(const Board& board, PieceColor color, int max_depth)
{
	auto compare = [](std::pair<int, Move> p1, std::pair<int, Move> p2)
	{
		return p1.first > p2.first;
	};
	auto possible_moves = get_all_possible_moves(board, color);
	std::vector<std::pair<int, Move>> evaluated_moves;

	for (int i = 0; i <= max_depth; i++)
	{
		evaluated_moves = get_evaluated_moves(board, color, i, possible_moves);
		std::sort(evaluated_moves.begin(), evaluated_moves.end(), compare);
		possible_moves.clear();
		for (const auto& eval_move : evaluated_moves)
			possible_moves.push_back(eval_move.second);
	}
	auto best_moves = get_best_moves(evaluated_moves);

	return get_random_move(best_moves);
}

void NegamaxAI::init_hashing_table()
{
	for (int x = 0; x < board_width; x++)
	{
		for (int y = 0; y < board_height; y++)
		{
			for (int piece_type = 0; piece_type < 12; piece_type++)
				hashing_table[x][y][piece_type] = rng.get_number(0, std::numeric_limits<uint64_t>::max());
		}
	}
}

inline static int get_hash_table_piece_type_index(uint32_t piece)
{
	int value = 0;
	auto color = get_piece_color(piece);
	if (color == PieceColor::BLACK)
		value = 1;
	switch (get_piece_type_value(piece))
	{
	case pawn_bit:		return value;
	case knight_bit:	return 2 + value;
	case bishop_bit:	return 4 + value;
	case rook_bit:		return 6 + value;
	case queen_bit:		return 8 + value;
	case king_bit:		return 10 + value;
	default:			assert(0);
	}
	return 0;
}

uint64_t NegamaxAI::hash_board(const Board& board, bool black) const
{
	constexpr uint64_t max_uint64_t = 0xFFFFFFFFFFFFFFFF;

	uint64_t hash = 0;
	for (int x = 0; x < board_width; x++)
	{
		for (int y = 0; y < board_height; y++)
		{
			if (!(board[x][y]))
				continue;
			const int index = get_hash_table_piece_type_index(board[x][y]);
			hash ^= hashing_table[x][y][index];
		}
	}
	if (black)
		return hash ^ max_uint64_t;
	return hash;
}

std::vector<std::pair<int, Move>> NegamaxAI::get_evaluated_moves(const Board& board, PieceColor color, int depth)
{
	std::vector<std::pair<int, Move>> evaluated_moves;
	auto possible_moves = get_all_possible_moves(board, color);
	for (const auto& move : possible_moves)
	{
		Board copy_board = board;
		make_move_with_automatic_promotion(copy_board, move);

		int val = evaluate_board_negamax(copy_board, get_next_player(color), depth, min_value, max_value);
		evaluated_moves.push_back({ val, move });
	}
	return evaluated_moves;
}

std::vector<std::pair<int, Move>> NegamaxAI::get_evaluated_moves_multi_threaded(const Board& board, PieceColor color, int depth)
{
	auto possible_moves = get_all_possible_moves(board, color);
	return get_evaluated_moves(board, color, depth, possible_moves);
}

std::vector<std::pair<int, Move>> NegamaxAI::get_evaluated_moves(const Board& board, PieceColor color, int depth, const std::vector<Move>& possible_moves)
{
	const auto processor_count = std::thread::hardware_concurrency();
	const int thread_count = std::max((unsigned int)1, processor_count);
	std::vector<std::thread> thread_pool;

	evaluated_moves.clear();
	current_index = 0;

	for (int i = 0; i < thread_count; i++)
		thread_pool.push_back(std::thread(&NegamaxAI::eval_multi_threaded, this, board, color, possible_moves, depth));

	for (auto& thread : thread_pool)
		thread.join();

	return evaluated_moves;
}

void NegamaxAI::eval_multi_threaded(const Board& board, PieceColor color, const std::vector<Move>& possible_moves, int depth)
{
	m_mutex.lock();
	int move_index = current_index;
	current_index++;
	m_mutex.unlock();

	while (move_index < possible_moves.size())
	{
		Move move = possible_moves[move_index];
		Board copy_board = board;
		make_move_with_automatic_promotion(copy_board, move);
		int val = evaluate_board_negamax(copy_board, get_next_player(color), depth, min_value, max_value);

		m_mutex.lock();
		evaluated_moves.push_back({ val, move });
		move_index = current_index;
		current_index++;
		m_mutex.unlock();
	}
}

Move NegamaxAI::get_random_move(const std::vector<Move>& moves)
{
	assert(moves.size());
	if (moves.size() == 0)
		return Move();

	return moves[rand() % moves.size()];
}

Move NegamaxAI::get_random_move(const std::vector<std::pair<int, Move>>& moves)
{
	assert(moves.size());
	if (moves.size() == 0)
		return Move();

	return moves[rand() % moves.size()].second;
}

static void set_move_to_front(std::vector<Move>& moves, const Move& move)
{
	for (int i = 0; i < moves.size(); i++)
	{
		const auto& buf = moves[i];
		if (buf.fromX == move.fromX && buf.fromY == move.fromY && buf.toX == move.toX && buf.toY == move.toY)
		{
			std::swap(moves[0], moves[i]);
			return;
		}
	}
}

static int get_piece_MVV_LVA_index(uint32_t piece) 
{
	switch (piece & piece_bit_mask)
	{
	case pawn_bit:		return 5;
	case knight_bit:	return 4;
	case bishop_bit:	return 3;
	case rook_bit:		return 2;
	case queen_bit:		return 1;
	case king_bit:		return 0;
	default:			return 6;
	}
}

static void sort_moves_by_MVV_LVA(const Board& board, std::vector<Move>& moves) 
{
	for (int i = 0; i < moves.size(); i++) 
	{
		int from_index = get_piece_MVV_LVA_index(board[moves[i].fromX][moves[i].fromY]);
		int to_index = get_piece_MVV_LVA_index(board[moves[i].toX][moves[i].toY]);

		int val = MVV_LVA[to_index][from_index];
	}
}

static std::vector<Move> generate_sorted_possible_moves(const Board& board, PieceColor current_player_color, const Move& tt_move)
{
	auto possible_moves = get_all_possible_moves(board, current_player_color);
	sort_moves_by_MVV_LVA(board, possible_moves);
	if (tt_move.fromX != -1)
		set_move_to_front(possible_moves, tt_move);

	return possible_moves;
}


int NegamaxAI::evaluate_board_negamax(const Board& board, PieceColor current_player_color, int depth, int alpha, int beta)
{
	const int initial_alpha = alpha;
	const uint64_t hash = hash_board(board, current_player_color == PieceColor::BLACK);

	int index = hash % max_tt_entries;
	Move tt_move{-1 };
	auto& entry = tt_table[index];
	{
		std::scoped_lock lock(entry.mut);
		if ((entry.hash != 0) && (entry.hash == hash) && (entry.depth >= depth))
		{
			tt_move = entry.best_move;
			if (entry.type == TTEntry::type::EXACT)
				return -entry.value;
			else if (entry.type == TTEntry::type::LOWER)
				alpha = std::max(alpha, entry.value);
			else if (entry.type == TTEntry::type::UPPER)
				beta = std::min(beta, entry.value);

			if (alpha >= beta)
				return -entry.value;
		}
	}

	const bool no_move_possible = !any_move_possible(board, current_player_color);
	const bool check = is_check(board, current_player_color);
	if (check && no_move_possible)
		return -(min_value - depth);
	if (!check && no_move_possible)
		return 0;

	if (depth == 0)
		return -static_board_evaluation(board, current_player_color);

	auto possible_moves = generate_sorted_possible_moves(board, current_player_color, tt_move);

	assert(possible_moves.size());
	Move best_move{};
	int move_value = min_value;
	for (const auto& move : possible_moves)
	{
		Board copy_board = board;
		make_move_with_automatic_promotion(copy_board, move);

		int eval_value = evaluate_board_negamax(copy_board, get_next_player(current_player_color), depth - 1, -beta, -alpha);
		if (eval_value > move_value) 
		{
			best_move = move;
			move_value = eval_value;
		}
		alpha = std::max(alpha, move_value);
		if (alpha >= beta)
			break;
	}

	std::scoped_lock lock(entry.mut);
	entry.value = move_value;
	entry.depth = depth;
	entry.hash = hash;
	entry.best_move = best_move;
	if (move_value <= initial_alpha)
		entry.type = TTEntry::type::UPPER;
	else if (move_value >= beta)
		entry.type = TTEntry::type::LOWER;
	else
		entry.type = TTEntry::type::EXACT;

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
	int piece_value = get_raw_piece_value(board[x][y]) + get_piece_position_value(board[x][y], piece_color, x, y);
	if (piece_color == current_player)
		return piece_value;

	return -piece_value;
}

int NegamaxAI::get_piece_position_value(uint32_t piece, PieceColor color, int x, int y)
{
	const uint32_t piece_type = get_piece_type_value(piece);
	switch (piece_type)
	{
	case pawn_bit:
		if (color == PieceColor::BLACK)
			return black_pawn_table[x][y];
		else
			return white_pawn_table[x][y];
	case knight_bit:
		if (color == PieceColor::BLACK)
			return black_knight_table[x][y];
		else
			return white_knight_table[x][y];
	case bishop_bit:
		if (color == PieceColor::BLACK)
			return black_bishop_table[x][y];
		else
			return white_bishop_table[x][y];
	case rook_bit:
		if (color == PieceColor::BLACK)
			return black_rook_table[x][y];
		else
			return white_rook_table[x][y];
	case queen_bit:
		if (color == PieceColor::BLACK)
			return black_queen_table[x][y];
		else
			return white_queen_table[x][y];
	case king_bit:
		if (color == PieceColor::BLACK)
			return black_king_early_game_table[x][y];
		else
			return white_king_early_game_table[x][y];
	default:
		assert(0);
	}
	return 0;
}

inline int NegamaxAI::get_raw_piece_value(uint32_t piece)
{
	const uint32_t piece_type = get_piece_type_value(piece);
	switch (piece_type)
	{
	case pawn_bit:		return 100;
	case knight_bit:	return 320;
	case bishop_bit:	return 330;
	case rook_bit:		return 500;
	case queen_bit:		return 900;
	case king_bit:		return 10000;
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
