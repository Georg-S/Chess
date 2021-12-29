#pragma once
#include <vector>
#include <set>
#include <string>
#include "Utility.h"
#include "MoveGenerator.h"

namespace ceg
{
	class ChessEngine
	{
	public:
		ChessEngine();
		std::vector<ceg::Move> get_all_possible_moves(const std::string& FEN_str);
		std::string make_move(const std::string& FEN_str, ceg::Move);
		std::string make_move_with_auto_promotion(const std::string& FEN_str, ceg::Move);

		uint64_t perft(const std::string& FEN_str, int depth);
		uint64_t perft(const std::string& FEN_str, int depth, const std::set<std::string>& possible_boards);

	private:
		void perft(const ceg::BitBoard& board, bool current_player_black, uint64_t* counter, int depth);
		void perft(const ceg::BitBoard& board, bool current_player_black, uint64_t* counter, int depth, const std::set<std::string>& possible_boards);
		ceg::MoveGenerator generator;
	};
}