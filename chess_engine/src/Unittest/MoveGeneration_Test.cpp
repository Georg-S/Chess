#include "Unittest/catch_amalgamated.hpp"
#include "Board.h"
#include "ChessEngine.h"
#include "MoveGenerator.h"

std::string initial_board_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

TEST_CASE("perft_start_board_depth_0_test", "MoveGeneration") 
{
	ceg::ChessEngine engine = ceg::ChessEngine();
	auto res = engine.perft(initial_board_FEN, 0);

	assert(res, 1);
}

/*
TEST_CASE("Buf_test", "MoveGeneration")
{

	ceg::MoveGenerator generator;
	uint64_t* arr = generator.black_pawn_normal_moves;
	ceg::print_bit_board(arr[0]);
	ceg::print_bit_board(arr[1]);
	ceg::print_bit_board(arr[2]);
	ceg::print_bit_board(arr[3]);
	ceg::print_bit_board(arr[4]);
	ceg::print_bit_board(arr[5]);
	ceg::print_bit_board(arr[6]);
	ceg::print_bit_board(arr[7]);
	ceg::print_bit_board(arr[8]);
	ceg::print_bit_board(arr[35]);

//	ceg::BitBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

//	board.print_board_to_console();
}
*/