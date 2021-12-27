#include "Unittest/catch_amalgamated.hpp"
#include "BitBoard.h"
#include "ChessEngine.h"
#include "MoveGenerator.h"

const std::string initial_board_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
ceg::ChessEngine engine = ceg::ChessEngine();

TEST_CASE("perft_start_board_depth_0_test", "MoveGeneration") 
{
	uint64_t perft_result = engine.perft(initial_board_FEN, 0);

	REQUIRE(perft_result == 1);
}

TEST_CASE("perft_start_board_depth_1_test", "MoveGeneration")
{
	uint64_t perft_result = engine.perft(initial_board_FEN, 1);

	REQUIRE(perft_result == 20);
}

TEST_CASE("perft_start_board_depth_2_test", "MoveGeneration")
{
	uint64_t perft_result = engine.perft(initial_board_FEN, 2);

	REQUIRE(perft_result == 400);
}

TEST_CASE("perft_start_board_depth_3_test", "MoveGeneration")
{
	uint64_t perft_result = engine.perft(initial_board_FEN, 3);

	REQUIRE(perft_result == 8902);
}

TEST_CASE("rook_move_count_white_test", "MoveGeneration") 
{
	const std::string test_board_fen_str = "k7/8/8/8/1b1R2b1/8/8/3n3K w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 15);
}

TEST_CASE("rook_move_count_black_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "K7/8/8/8/1B1r2B1/8/8/3N3k b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 15);
}

TEST_CASE("bishop_move_count_white_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "k6n/n7/8/8/3B4/8/1b6/7K w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 15);
}

TEST_CASE("bishop_move_count_black_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "K6N/N7/8/8/3b4/8/1B6/7k b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 15);
}

TEST_CASE("queen_move_count_white_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "k6n/n7/3p4/8/2rQ1p2/8/1b1p4/7K w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 22);
}

TEST_CASE("queen_move_count_black_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "K6N/N7/3P4/8/2Rq1P2/8/1B1P4/7k b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 22);
}

TEST_CASE("knight_move_count_white_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "k7/8/8/r3p3/2N5/8/1N6/7K w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 13);
}

TEST_CASE("knight_move_count_black_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "K7/8/8/R3P3/2n5/8/1n6/7k b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 13);
}

TEST_CASE("pawn_move_count_white", "MoveGeneration")
{
	const std::string test_board_fen_str = "k7/8/8/7p/6pP/p1pPp3/1P2P1P1/7K w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 8);
}

TEST_CASE("pawn_move_count_black", "MoveGeneration")
{
	const std::string test_board_fen_str = "k7/1p1p2p1/3PpP1P/pP6/P7/8/8/7K b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 8);
}

TEST_CASE("simple_check_move_count_white_test_1", "MoveGeneration")
{
	const std::string test_board_fen_str = "k3r3/8/8/8/8/8/4K3/8 w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 6);
}

TEST_CASE("simple_check_move_count_black_test_1", "MoveGeneration")
{
	const std::string test_board_fen_str = "K3R3/8/8/8/8/8/4k3/8 b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 6);
}

TEST_CASE("simple_check_move_count_white_test_2", "MoveGeneration")
{
	const std::string test_board_fen_str = "k3r3/8/8/8/8/8/4Kq2/8 w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 3);
}

TEST_CASE("simple_check_move_count_black_test_2", "MoveGeneration")
{
	const std::string test_board_fen_str = "K3R3/8/8/8/8/8/4kQ2/8 b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 3);
}

TEST_CASE("simple_check_mate_move_count_white_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "k7/8/8/8/8/8/3qKq2/8 w - - 0 1";

	uint64_t perft_perft_resultult = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_perft_resultult == 1);
}

TEST_CASE("simple_check_mate_move_count_black_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "K7/8/8/8/8/8/3QkQ2/8 b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 1);
}

/*
 
TEST_CASE("Buf_test", "MoveGeneration")
{
	ceg::ChessEngine engine = ceg::ChessEngine();
	ceg::MoveGenerator gen = ceg::MoveGenerator();
	ceg::print_bit_board(gen.rook_mask[35]);
}
*/