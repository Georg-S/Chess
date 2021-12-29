#include "Unittest/catch_amalgamated.hpp"
#include "BitBoard.h"
#include "ChessEngine.h"
#include "MoveGenerator.h"

const std::string initial_board_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
const std::string perft_test_board_2 = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ";
const std::string perft_test_board_3 = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - ";
static ceg::ChessEngine engine = ceg::ChessEngine();


/*
TEST_CASE("perft_test_board_2_depth_3_test", "MoveGeneration")
{
	uint64_t perft_result = engine.perft(perft_test_board_2, 3);

	REQUIRE(perft_result == 97862);
}
*/

TEST_CASE("perft_test_board_3_depth_3_test", "MoveGeneration")
{
	uint64_t perft_result = engine.perft(perft_test_board_3, 3);

	REQUIRE(perft_result == 2812);
}