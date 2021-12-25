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
	auto splitted = string_split(FEN_str, " ");
	if (splitted.size() < 4) 
	{
		assert(!"Invalid FEN input string");
		return 0;
	}

	bool current_player_black = (splitted[1].at(0) == 'b');
	ceg::BitBoard board(splitted[0], splitted[2], splitted[3]);
	uint64_t counter = 0;
	perft(board, current_player_black, &counter, depth);

	return counter;
}

void ceg::ChessEngine::perft(const ceg::BitBoard& board, bool current_player_black, uint64_t* counter, int depth)
{
	if (depth == 0)
	{
		(*counter)++;
		return;
	}

	auto moves = generator.get_all_possible_moves(board, current_player_black);
	for (const auto& move : moves)
	{
		ceg::BitBoard copy_board = board;
		generator.make_move(copy_board, move);
		perft(copy_board, !current_player_black, counter, depth - 1);
	}
}
