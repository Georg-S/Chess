#include "Unittest/catch_amalgamated.hpp"
#include "BitBoard.h"
#include "ChessEngine.h"
#include "MoveGenerator.h"

const std::string initial_board_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
const std::string perft_test_board_2 = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ";
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

TEST_CASE("perft_start_board_depth_4_test", "MoveGeneration")
{
	uint64_t perft_result = engine.perft(initial_board_FEN, 4);

	REQUIRE(perft_result == 197281);
}

TEST_CASE("perft_test_board_2_depth_1_test", "MoveGeneration")
{
	uint64_t perft_result = engine.perft(perft_test_board_2, 1);

	REQUIRE(perft_result == 48);
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

TEST_CASE("simple_bishop_check_move_count_white_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "k7/8/5b2/8/3K4/1b6/8/8 w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 4);
}

TEST_CASE("simple_bishop_check_move_count_black_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "K7/8/5B2/8/3k4/1B6/8/8 b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 4);
}

TEST_CASE("white_king_cant_move_on_attacked_square_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "8/8/3K4/8/3k4/8/8/8 w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 5);
}

TEST_CASE("black_king_cant_move_on_attacked_square_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "8/8/3K4/8/3k4/8/8/8 b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 5);
}

TEST_CASE("white_king_check_by_knight_cant_move_on_attacked_square_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "8/8/1n1K4/5n2/8/8/8/7k w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 5);
}

TEST_CASE("black_king_check_by_knight_cant_move_on_attacked_square_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "8/8/1N1k4/5N2/8/8/8/7K b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 5);
}

TEST_CASE("white_king_check_by_pawn_cant_move_on_attacked_square_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "k7/8/8/6p1/3p1p2/4K3/8/8 w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 7);
}

TEST_CASE("black_king_check_by_pawn_cant_move_on_attacked_square_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "8/8/4k3/3P1P2/2P5/8/8/7K b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 7);
}

TEST_CASE("white_king_double_check_can_only_move_king_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "k2r4/8/8/8/8/5n2/3K4/7R w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 5);
}

TEST_CASE("black_king_double_check_can_only_move_king_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "K2R4/8/8/8/8/5N2/3k4/7r b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 5);
}

TEST_CASE("white_rook_pinned_by_rook_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "k7/8/8/8/1K1R2r1/8/8/8 w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 12);
}

TEST_CASE("black_rook_pinned_by_rook_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "K7/8/8/8/1k1r2R1/8/8/8 b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 12);
}

TEST_CASE("white_rook_pinned_by_bishop_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "k4b2/8/3R4/8/1K6/8/8/8 w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 8);
}

TEST_CASE("black_rook_pinned_by_bishop_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "K4B2/8/3r4/8/1k6/8/8/8 b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 8);
}

TEST_CASE("white_rook_pinned_by_queen_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "k7/8/8/8/1K6/2R5/8/4q3 w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 7);
}

TEST_CASE("black_rook_pinned_by_queen_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "K7/8/8/8/1k6/2r5/8/4Q3 b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 7);
}

TEST_CASE("white_pawn_pinned_by_queen_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "k7/8/8/8/1K6/2P5/8/4q3 w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 7);
}

TEST_CASE("black_pawn_pinned_by_queen_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "K7/8/8/8/1k6/2p5/8/4Q3 b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 7);
}

TEST_CASE("white_is_check_queen_has_limited_possible_moves", "MoveGeneration")
{
	const std::string test_board_fen_str = "k7/8/8/8/1K4r1/8/8/3Q4 w - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 8);
}

TEST_CASE("black_is_check_queen_has_limited_possible_moves", "MoveGeneration")
{
	const std::string test_board_fen_str = "K7/8/8/8/1k4R1/8/8/3q4 b - - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 8);
}

TEST_CASE("white_can_castle_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "r3k2r/8/8/8/8/8/8/R3K2R w KQ - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 26);
}

TEST_CASE("black_can_castle_test", "MoveGeneration")
{
	const std::string test_board_fen_str = "r3k2r/8/8/8/8/8/8/R3K2R b kq - 0 1";

	uint64_t perft_result = engine.perft(test_board_fen_str, 1);

	REQUIRE(perft_result == 26);
}