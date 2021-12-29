#include "ChessEngine.h"

ceg::ChessEngine::ChessEngine()
{
	generator = MoveGenerator();
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

std::string ceg::ChessEngine::make_move(const std::string& FEN_str, ceg::Move)
{
	return std::string();
}

std::string ceg::ChessEngine::make_move_with_auto_promotion(const std::string& FEN_str, ceg::Move)
{
	return std::string();
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

	auto moves = generator.get_all_possible_moves(board, current_player_black);
	for (const auto& move : moves)
	{
		ceg::BitBoard copy_board = board;
		generator.make_move(copy_board, move);
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
