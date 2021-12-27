#include "Unittest/catch_amalgamated.hpp"
#include "BitBoard.h"
#include "ChessEngine.h"
#include "MoveGenerator.h"

const std::string initial_board_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

TEST_CASE("perft_start_board_depth_0_test", "MoveGeneration") 
{
	ceg::ChessEngine engine = ceg::ChessEngine();
	auto res = engine.perft(initial_board_FEN, 0);

	REQUIRE(res == 1);
}

TEST_CASE("perft_start_board_depth_1_test", "MoveGeneration")
{
	ceg::ChessEngine engine = ceg::ChessEngine();
	auto res = engine.perft(initial_board_FEN, 1);

	REQUIRE(res == 20);
}

TEST_CASE("perft_start_board_depth_2_test", "MoveGeneration")
{
	ceg::ChessEngine engine = ceg::ChessEngine();
	auto res = engine.perft(initial_board_FEN, 2);

	REQUIRE(res == 400);
}

TEST_CASE("rook_move_count_test", "MoveGeneration") 
{
	const std::string rook_test = "k7/8/8/8/1b1R2b1/8/8/3n3K w - - 0 1";
	ceg::ChessEngine engine = ceg::ChessEngine();

	auto res = engine.perft(rook_test, 1);

	REQUIRE(res == 15);
}

TEST_CASE("bishop_move_count_test", "MoveGeneration")
{
	const std::string bishop_test = "k6n/n7/8/8/3B4/8/1b6/7K w - - 0 1";
	ceg::ChessEngine engine = ceg::ChessEngine();

	auto res = engine.perft(bishop_test, 1);

	REQUIRE(res == 15);
}

TEST_CASE("queen_move_count_white_test", "MoveGeneration")
{
	const std::string queen_test = "k6n/n7/3p4/8/2rQ1p2/8/1b1p4/7K w - - 0 1";
	ceg::ChessEngine engine = ceg::ChessEngine();

	auto res = engine.perft(queen_test, 1);

	REQUIRE(res == 22);
}

TEST_CASE("queen_move_count_black_test", "MoveGeneration")
{
	const std::string queen_test = "K6N/N7/3P4/8/2Rq1P2/8/1B1P4/7k b - - 0 1";
	ceg::ChessEngine engine = ceg::ChessEngine();

	auto res = engine.perft(queen_test, 1);

	REQUIRE(res == 22);
}

/*
TEST_CASE("perft_start_board_depth_3_test", "MoveGeneration")
{
	ceg::ChessEngine engine = ceg::ChessEngine();
	auto res = engine.perft(initial_board_FEN, 3);

	REQUIRE(res == 8902);
}

TEST_CASE("Buf_test", "MoveGeneration")
{
	ceg::ChessEngine engine = ceg::ChessEngine();
	ceg::MoveGenerator gen = ceg::MoveGenerator();
	ceg::print_bit_board(gen.rook_mask[35]);
}
*/