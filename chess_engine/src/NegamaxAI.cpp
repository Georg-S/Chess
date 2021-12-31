#include "NegamaxAI.h"

ceg::NegamaxAI::NegamaxAI()
{
	srand(time(NULL));
	init_hashing_table();
	tt_table = new TTEntry[max_tt_entries];
	move_generator = std::make_unique<MoveGenerator>();
}

ceg::NegamaxAI::~NegamaxAI()
{
	delete[] tt_table;
}

ceg::InternalMove ceg::NegamaxAI::get_move(const ceg::BitBoard& board, bool color_is_black, int depth)
{
	/*
	auto evaluated_moves = get_evaluated_moves(board, color, depth);
	auto evaluated_moves = get_evaluated_moves_multi_threaded(board, color, depth);
	auto best_moves = get_best_moves(evaluated_moves);

	return get_random_move(best_moves);
	*/
	return iterative_deepening(board, color_is_black, depth);
}

ceg::InternalMove ceg::NegamaxAI::iterative_deepening(const ceg::BitBoard& board, bool color_is_black, int max_depth)
{
	auto possible_moves = move_generator->get_all_possible_moves(board, color_is_black);
	std::vector<EvalMove> evaluated_moves;

	for (int i = 0; i <= max_depth; i++)
	{
		evaluated_moves = get_evaluated_moves(board, color_is_black, i, possible_moves);
		std::sort(evaluated_moves.begin(), evaluated_moves.end(), operator>);
		possible_moves.clear();
		for (const auto& eval_move : evaluated_moves)
			possible_moves.push_back(eval_move.move);
	}
	auto best_moves = get_best_moves(evaluated_moves);

	return get_random_move(best_moves);
}

void ceg::NegamaxAI::init_hashing_table()
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

static int get_hash_table_piece_type_index(const ceg::BitBoard& board, int index)
{
	int value = 0;
	bool is_black_piece = ceg::is_bit_set(board.black_pieces.occupied, index);
	if (is_black_piece)
		value = 1;

	const ceg::Pieces* pieces = is_black_piece ? &(board.black_pieces) : &(board.white_pieces);

	if (ceg::is_bit_set(pieces->pawns, index)) return value;
	else if (ceg::is_bit_set(pieces->knights, index)) return 2 + value;
	else if (ceg::is_bit_set(pieces->bishops, index)) return 4 + value;
	else if (ceg::is_bit_set(pieces->rooks, index)) return 6 + value;
	else if (ceg::is_bit_set(pieces->queens, index)) return 8 + value;
	else if (ceg::is_bit_set(pieces->king, index)) return 10 + value;

	assert(!"Invalid piece for hashing");
	return 0;
}

uint64_t ceg::NegamaxAI::hash_board(const ceg::BitBoard& board, bool color_is_black) const
{
	constexpr uint64_t max_uint64_t = 0xFFFFFFFFFFFFFFFF;

	uint64_t hash = 0;
	for (int x = 0; x < board_width * board_height; x++)
	{
		for (int y = 0; y < board_height; y++)
		{
			if(!is_bit_set(board.occupied, x, y))
				continue;
			//TODO refactor hashing table to use linear index
			const int index = get_hash_table_piece_type_index(board, x+y*8);
			hash ^= hashing_table[x][y][index];
		}
	}
	if (color_is_black)
		return hash ^ max_uint64_t;
	return hash;
}

static bool get_next_player(bool black) 
{
	return !black;
}

std::vector<ceg::EvalMove> ceg::NegamaxAI::get_evaluated_moves(const ceg::BitBoard& board, bool color_is_black, int depth)
{
	std::vector<EvalMove> evaluated_moves;
	auto possible_moves = move_generator->get_all_possible_moves(board, color_is_black);
	for (const auto& move : possible_moves)
	{
		ceg::BitBoard copy_board = board;
		move_generator->make_move_with_auto_promotion(copy_board, move);

		int val = evaluate_board_negamax(copy_board, get_next_player(color_is_black), depth, min_value, max_value);
		evaluated_moves.push_back({ move, val});
	}
	return evaluated_moves;
}

std::vector<ceg::EvalMove> ceg::NegamaxAI::get_evaluated_moves_multi_threaded(const ceg::BitBoard& board, bool color_is_black, int depth)
{
	auto possible_moves = move_generator->get_all_possible_moves(board, color_is_black);
	return get_evaluated_moves(board, color_is_black, depth, possible_moves);
}

std::vector<ceg::EvalMove> ceg::NegamaxAI::get_evaluated_moves(const ceg::BitBoard& board, bool color_is_black, int depth, const std::vector<ceg::InternalMove>& possible_moves)
{
	const auto processor_count = std::thread::hardware_concurrency();
	const int thread_count = std::max((unsigned int)1, processor_count);
	std::vector<std::thread> thread_pool;

	evaluated_moves.clear();
	current_index = 0;

	for (int i = 0; i < thread_count; i++)
		thread_pool.push_back(std::thread(&NegamaxAI::eval_multi_threaded, this, board, color_is_black, possible_moves, depth));

	for (auto& thread : thread_pool)
		thread.join();

	return evaluated_moves;
}

void ceg::NegamaxAI::eval_multi_threaded(const ceg::BitBoard& board, bool color_is_black, const std::vector<ceg::InternalMove>& possible_moves, int depth)
{
	m_mutex.lock();
	int move_index = current_index;
	current_index++;
	m_mutex.unlock();

	while (move_index < possible_moves.size())
	{
		ceg::InternalMove move = possible_moves[move_index];
		ceg::BitBoard copy_board = board;
		move_generator->make_move_with_auto_promotion(copy_board, move);
		int val = evaluate_board_negamax(copy_board, get_next_player(color_is_black), depth, min_value, max_value);

		m_mutex.lock();
		evaluated_moves.push_back({ move, val});
		move_index = current_index;
		current_index++;
		m_mutex.unlock();
	}
}

ceg::InternalMove ceg::NegamaxAI::get_random_move(const std::vector<ceg::InternalMove>& moves)
{
	assert(moves.size());
	if (moves.size() == 0)
		return ceg::InternalMove();

	return moves[rand() % moves.size()];
}

ceg::InternalMove ceg::NegamaxAI::get_random_move(const std::vector<std::pair<int, ceg::InternalMove>>& moves)
{
	assert(moves.size());
	if (moves.size() == 0)
		return ceg::InternalMove();

	return moves[rand() % moves.size()].second;
}

static void set_move_to_front(std::vector<ceg::InternalMove>& moves, const ceg::InternalMove& move)
{
	for (int i = 0; i < moves.size(); i++)
	{
		const auto& buf = moves[i];
		if (buf.from == move.from && buf.to == move.to)
		{
			std::swap(moves[0], moves[i]);
			return;
		}
	}
}

static int get_piece_MVV_LVA_index(const ceg::BitBoard& board, int index) 
{
	// TODO check if this can be done more efficient
	if (!ceg::is_bit_set(board.occupied, index))
		return 6;

	if (ceg::is_bit_set(board.black_pieces.pawns | board.white_pieces.pawns, index)) return 5;
	if (ceg::is_bit_set(board.black_pieces.knights | board.white_pieces.knights, index)) return 4;
	if (ceg::is_bit_set(board.black_pieces.bishops | board.white_pieces.bishops, index)) return 3;
	if (ceg::is_bit_set(board.black_pieces.rooks | board.white_pieces.rooks, index)) return 2;
	if (ceg::is_bit_set(board.black_pieces.queens | board.white_pieces.queens, index)) return 1;
	if (ceg::is_bit_set(board.black_pieces.king | board.white_pieces.king, index)) return 0;

	return 6;
}

static void sort_moves_by_MVV_LVA(const ceg::BitBoard& board, std::vector<ceg::EvalMove>& moves) 
{
	for (int i = 0; i < moves.size(); i++) 
	{
		const ceg::InternalMove& move = moves[i].move;
		int from_index = get_piece_MVV_LVA_index(board, move.from);
		int to_index = get_piece_MVV_LVA_index(board, move.to);

		moves[i].value = ceg::MVV_LVA[to_index][from_index];
	}
	std::sort(moves.begin(), moves.end(), ceg::operator>);
}

std::vector<ceg::InternalMove> ceg::NegamaxAI::generate_sorted_possible_moves(const ceg::BitBoard& board, bool color_is_black, const ceg::InternalMove& tt_move)
{
	std::vector<ceg::EvalMove> eval_moves;
	auto possible_moves = move_generator->get_all_possible_moves(board, color_is_black);
	for (const auto& move : possible_moves)
		eval_moves.push_back({ move, 0 });

	sort_moves_by_MVV_LVA(board, eval_moves);

	std::vector<ceg::InternalMove> sorted_moves;
	for (const auto& eval_move : eval_moves)
		sorted_moves.push_back(eval_move.move);

	if (tt_move.from != -1)
		set_move_to_front(sorted_moves, tt_move);

	return sorted_moves;
}


int ceg::NegamaxAI::evaluate_board_negamax(const ceg::BitBoard& board, bool color_is_black, int depth, int alpha, int beta)
{
	const int initial_alpha = alpha;
	const uint64_t hash = hash_board(board, color_is_black);

	int index = hash % max_tt_entries;
	ceg::InternalMove tt_move{-1 };
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

	auto state = move_generator->get_state_information(board, color_is_black);
	if ((state.check_counter >= 1) && (state.possible_moves.size() == 0))
		return -(min_value - depth);
	if (state.possible_moves.size() == 0)
		return 0;

	if (depth == 0)
		return -static_board_evaluation(board, color_is_black);

	//TODO Refactor to be correct
	auto possible_moves = generate_sorted_possible_moves(board, color_is_black, tt_move);
	if (possible_moves.size() == 0)
		return 0;

	assert(possible_moves.size());
	ceg::InternalMove best_move{};
	int move_value = min_value;
	for (const auto& move : possible_moves)
	{
		ceg::BitBoard copy_board = board;
		move_generator->make_move_with_auto_promotion(copy_board, move);

		int eval_value = evaluate_board_negamax(copy_board, get_next_player(color_is_black), depth - 1, -beta, -alpha);
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

int ceg::NegamaxAI::static_board_evaluation(const ceg::BitBoard& board, bool current_player_black)
{
	return 0;
	int value = 0;
	for (int x = 0; x < board_width; x++)
	{
		for (int y = 0; y < board_height; y++)
		{
			if (!is_bit_set(board.occupied, x, y))
				continue;

//			value += get_piece_value(board, current_player_black, x, y);
		}
	}
	return value;
}
/*
int ceg::NegamaxAI::get_piece_value(const ceg::BitBoard& board, bool current_player_black, int x, int y)
{
	bool piece_color_black = ceg::is_bit_set(board.black_pieces.occupied, x, y);

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
*/

std::vector<ceg::InternalMove> ceg::NegamaxAI::get_best_moves(std::vector<ceg::EvalMove> moves)
{
	std::vector<ceg::InternalMove> best_moves;
	assert(moves.size());
	if (moves.size() == 0)
		return best_moves;

	auto max_element = std::max_element(moves.begin(), moves.end());

	int highest_value = (*(max_element)).value;
	for (const auto& eval_move : moves)
	{
		if (eval_move.value == highest_value)
			best_moves.push_back(eval_move.move);
	}

	return best_moves;
}
