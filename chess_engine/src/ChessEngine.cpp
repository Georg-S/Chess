#include "ChessEngine.h"

ceg::ChessEngine::ChessEngine()
{
	move_generator = std::make_unique<ceg::MoveGenerator>();
	ai = std::make_unique<ceg::NegamaxAI>(move_generator.get());
}

ceg::BitBoard ceg::ChessEngine::get_initial_board() const
{
	return get_board_by_FEN_str(initial_board_str);
}

ceg::PieceColor ceg::ChessEngine::get_next_player(PieceColor color)
{
	return (color == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
}

std::vector<ceg::Move> ceg::ChessEngine::get_all_possible_moves(const std::string& FEN_str)
{
	auto result = std::vector<ceg::Move>();

	auto splitted = string_split(FEN_str, " ");
	if (splitted.size() < 2)
		return result;

	bool current_player_black = (splitted[1].at(0) == 'b');


	return result;
}

std::vector<ceg::Move> ceg::ChessEngine::get_all_possible_moves_for_piece(const ceg::BitBoard& board, int piece_x, int piece_y)
{
	const int index = to_linear_idx(piece_x, piece_y);
	if (!is_bit_set(board.occupied, index))
		return std::vector<ceg::Move>();

	bool black = false;
	if (is_bit_set(board.black_pieces.occupied, index))
		black = true;

	auto moves = move_generator->get_all_possible_moves(board, black);

	std::vector<ceg::Move> result;
	for (const auto& move : moves)
	{
		if (move.from == index)
			result.push_back(move);
	}

	return result;
}

ceg::Move ceg::ChessEngine::get_ai_move(const ceg::BitBoard& board, bool current_player_black, int depth)
{
	return	ai->get_move(board, current_player_black, depth);
}

ceg::Move ceg::ChessEngine::get_ai_move(const ceg::BitBoard& board, PieceColor color, int depth)
{
	return get_ai_move(board, to_bool(color), depth);
}

void ceg::ChessEngine::make_move(ceg::BitBoard& board, ceg::Move move)
{
	move_generator->make_move(board, convert_to_internal(move));
}

void ceg::ChessEngine::make_move_with_auto_promo(ceg::BitBoard& board, ceg::Move move)
{
	move_generator->make_move_with_auto_promotion(board, convert_to_internal(move));
}

bool ceg::ChessEngine::is_move_valid(const ceg::BitBoard& board, const ceg::Move& move)
{
	if (!is_bit_set(board.occupied, move.from_x, move.from_y))
		return false;

	const int linear_from = to_linear_idx(move.from_x, move.from_y);
	const int linear_to = to_linear_idx(move.to_x, move.to_y);
	bool black = is_bit_set(board.black_pieces.occupied, move.from_x, move.from_y);
	auto possible_moves = move_generator->get_all_possible_moves(board, black);
	for (const auto& gen_move : possible_moves) 
	{
		if ((gen_move.from == linear_from) && (gen_move.to == linear_to))
			return true;
	}

	return false;
}

bool ceg::ChessEngine::has_pawn_reached_end_of_board(ceg::BitBoard& board)
{
	uint64_t pawn_mask = board.black_pieces.pawns | board.white_pieces.pawns;
	for (int i = 0; i < 8; i++)
	{
		if (is_bit_set(pawn_mask, i, 0))
			return true;
		if (is_bit_set(pawn_mask, i, 7))
			return true;
	}
	return false;
}

bool ceg::ChessEngine::is_game_over(const ceg::BitBoard& board, PieceColor color)
{
	auto moves = move_generator->get_all_possible_moves(board, to_bool(color));

	return moves.size() == 0;
}

bool ceg::ChessEngine::is_field_occupied(const ceg::BitBoard& board, int x, int y)
{
	return is_bit_set(board.occupied, x, y);
}

ceg::PieceColor ceg::ChessEngine::get_piece_color(const ceg::BitBoard& board, int x, int y)
{
	assert(is_field_occupied(board, x, y));
	if (is_bit_set(board.black_pieces.occupied, x, y))
		return PieceColor::BLACK;
	else
		return PieceColor::WHITE;
}

void ceg::ChessEngine::set_piece(ceg::BitBoard& board, Piece piece, PieceColor color, int x, int y)
{
	const int linear_idx = to_linear_idx(x, y);
	board.clear_bits_at_position(linear_idx);
	bool black = to_bool(color);
	Pieces* pieces = black ? &(board.black_pieces) : &(board.white_pieces);

	switch (piece)
	{
	case ceg::Piece::PAWN:
		set_bit(pieces->pawns, linear_idx);
		break;
	case ceg::Piece::BISHOP:
		set_bit(pieces->bishops, linear_idx);
		break;
	case ceg::Piece::KNIGHT:
		set_bit(pieces->knights, linear_idx);
		break;
	case ceg::Piece::ROOK:
		set_bit(pieces->rooks, linear_idx);
		break;
	case ceg::Piece::QUEEN:
		set_bit(pieces->queens, linear_idx);
		break;
	case ceg::Piece::KING:
		set_bit(pieces->king, linear_idx);
		break;
	default:
		break;
	}
	board.update_occupied();
}

bool ceg::ChessEngine::is_check_mate(ceg::BitBoard& board, PieceColor color)
{
	auto possible_moves = move_generator->get_all_possible_moves(board, to_bool(color));
	auto check_info = move_generator->get_check_info(board, to_bool(color));

	if (possible_moves.size() == 0 && check_info.check_counter >= 1)
		return true;

	return false;
}

bool ceg::ChessEngine::is_stale_mate(ceg::BitBoard& board, PieceColor color)
{
	auto possible_moves = move_generator->get_all_possible_moves(board, to_bool(color));
	auto check_info = move_generator->get_check_info(board, to_bool(color));

	if (possible_moves.size() == 0 && check_info.check_counter == 0)
		return true;

	return false;
}

uint64_t ceg::ChessEngine::perft(const std::string& FEN_str, int depth)
{
	return perft(FEN_str, depth, nullptr, nullptr);
}

std::set<std::string> ceg::ChessEngine::perft_get_set(const std::string& FEN_str, int depth)
{
	std::set<std::string> result_set;

	perft(FEN_str, depth, &result_set, nullptr);

	return result_set;
}

std::map<std::string, int>  ceg::ChessEngine::perft_get_map(const std::string& FEN_str, int depth)
{
	std::map<std::string, int> result_map;

	perft(FEN_str, depth, nullptr, &result_map);

	return result_map;
}

ceg::BitBoard ceg::ChessEngine::get_board_by_FEN_str(const std::string& FEN_str) const
{
	auto splitted = string_split(FEN_str, " ");
	if (splitted.size() < 4)
	{
		assert(!"Invalid FEN input string");
		return 0;
	}
	return 	ceg::BitBoard(splitted[0], splitted[2], splitted[3]);
}

bool ceg::ChessEngine::to_bool(ceg::PieceColor color)
{
	return (color == PieceColor::BLACK) ? true : false;
}

ceg::InternalMove ceg::ChessEngine::convert_to_internal(const ceg::Move& move)
{
	return ceg::InternalMove{ to_linear_idx(move.from_x, move.from_y), to_linear_idx(move.to_x, move.to_y) };
}

uint64_t ceg::ChessEngine::perft(const std::string& FEN_str, int depth, std::set<std::string>* out_set, std::map<std::string, int>* out_map)
{
	auto splitted = string_split(FEN_str, " ");
	if (splitted.size() < 4)
	{
		assert(!"Invalid FEN input string");
		return 0;
	}

	bool current_player_black = (splitted[1].at(0) == 'b');
	ceg::BitBoard board(splitted[0], splitted[2], splitted[3]);
	return perft(board, current_player_black, depth, out_set, out_map);
}

uint64_t ceg::ChessEngine::perft(const ceg::BitBoard& board, bool current_player_black, int depth, std::set<std::string>* out_set, std::map<std::string, int>* out_map)
{
	if (depth == 0)
		return 1ULL;

	uint64_t nodes = 0;

	auto moves = move_generator->get_all_possible_moves(board, current_player_black);
	for (const auto& move : moves)
	{
		ceg::BitBoard copy_board = board;
		move_generator->make_move(copy_board, move);
		if (out_set)
			out_set->insert(copy_board.to_FEN_string());

		if (out_map)
		{
			std::string fen_str = copy_board.to_FEN_string();
			if (out_map->find(fen_str) == out_map->end())
				out_map->insert({ fen_str, 1 });
			else
				out_map->at(fen_str) += 1;
		}
		nodes += perft(copy_board, !current_player_black, depth - 1, out_set, out_map);
	}
	return nodes;
}
