#include "Unittest/catch_amalgamated.hpp"
#include "BitBoard.h"

TEST_CASE("to_FEN_string_test_1", "BitBoard")
{
	const std::string board_initial_str = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	ceg::BitBoard board = ceg::BitBoard(board_initial_str);

	REQUIRE(board_initial_str == board.to_FEN_string());
}

TEST_CASE("to_FEN_string_test_2", "BitBoard")
{
	const std::string board_initial_str = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R";
	ceg::BitBoard board = ceg::BitBoard(board_initial_str);

	REQUIRE(board_initial_str == board.to_FEN_string());
}