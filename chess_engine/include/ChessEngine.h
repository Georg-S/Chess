#pragma once
#include <vector>
#include <set>
#include <string>
#include <map>
#include "Utility.h"
#include "MoveGenerator.h"

namespace ceg
{
	enum PerftOption { NONE, GET_SET, GET_MAP };
	class ChessEngine
	{
	public:
		ChessEngine();
		std::vector<ceg::Move> get_all_possible_moves(const std::string& FEN_str);
		std::string make_move(const std::string& FEN_str, ceg::Move);
		std::string make_move_with_auto_promotion(const std::string& FEN_str, ceg::Move);

		uint64_t perft(const std::string& FEN_str, int depth);
		std::set<std::string> perft_get_set(const std::string& FEN_str, int depth);
		std::map<std::string, int> perft_get_map(const std::string& FEN_str, int depth);

	private:
		uint64_t perft(const std::string& FEN_str, int depth, std::set<std::string>* out_set, std::map<std::string, int>* out_map);
		uint64_t perft(const ceg::BitBoard& board, bool current_player_black, int depth, std::set<std::string>* out_set, std::map<std::string, int>* out_map);
		ceg::MoveGenerator generator;
	};
}