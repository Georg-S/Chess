#include "Unittest/catch_amalgamated.hpp"
#include "ChessEngine.h"

static const std::string test_board_1_str = "k2q4/8/8/8/8/8/PPP5/K7 b - - 0 1";
static const std::string test_board_2_str = "k7/8/8/8/3q4/8/PPP5/K5Q1 b - - 0 1";
static const std::string test_board_3_str = "k7/8/3q4/8/4K3/8/8/1Q6 b - - 0 1";
static const std::string test_board_4_str = "k6K/2PqB3/8/8/8/8/8/8 b - - 0 1";
static ceg::ChessEngine engine = ceg::ChessEngine();

TEST_CASE("Test_board_1_ai_depth_0", "[board_1]")
{
	ceg::BitBoard test_board = ceg::BitBoard(test_board_1_str);
	ceg::Move move = engine.get_ai_move(test_board, true, 0);

	REQUIRE(move.to_x == 3);
	REQUIRE(move.to_y == 7);
}

TEST_CASE("Test_board_1_ai_depth_1", "[board_1]")
{
	ceg::BitBoard test_board = ceg::BitBoard(test_board_1_str);
	ceg::Move move = engine.get_ai_move(test_board, true, 1);

	REQUIRE(move.to_x == 3);
	REQUIRE(move.to_y == 7);
}

TEST_CASE("Test_board_1_ai_depth_2", "[board_1]")
{
	ceg::BitBoard test_board = ceg::BitBoard(test_board_1_str);
	ceg::Move move = engine.get_ai_move(test_board, true, 2);

	REQUIRE(move.to_x == 3);
	REQUIRE(move.to_y == 7);
}

TEST_CASE("Test_board_2_ai_depth_0", "[board_2]")
{
	ceg::BitBoard test_board = ceg::BitBoard(test_board_2_str);
	ceg::Move move = engine.get_ai_move(test_board, true, 0);

	REQUIRE(move.to_x == 6);
	REQUIRE(move.to_y == 7);
}

TEST_CASE("Test_board_2_ai_depth_1", "[board_2]")
{
	ceg::BitBoard test_board = ceg::BitBoard(test_board_2_str);
	ceg::Move move = engine.get_ai_move(test_board, true, 1);

	REQUIRE(move.to_x == 6);
	REQUIRE(move.to_y == 7);
}

TEST_CASE("Test_board_2_ai_depth_2", "[board_2]")
{
	ceg::BitBoard test_board = ceg::BitBoard(test_board_2_str);
	ceg::Move move = engine.get_ai_move(test_board, true, 2);

	REQUIRE(move.to_x == 6);
	REQUIRE(move.to_y == 7);
}

TEST_CASE("Test_board_3_ai_depth_2", "[board_3]")
{
	ceg::BitBoard test_board = ceg::BitBoard(test_board_3_str);
	ceg::Move move = engine.get_ai_move(test_board, true, 2);

	REQUIRE(move.to_x == 6);
	REQUIRE(move.to_y == 2);
}

TEST_CASE("Test_board_3_ai_depth_3", "[board_3]")
{
	ceg::BitBoard test_board = ceg::BitBoard(test_board_3_str);
	ceg::Move move = engine.get_ai_move(test_board, true, 3);

	REQUIRE(move.to_x == 6);
	REQUIRE(move.to_y == 2);
}

TEST_CASE("Test_board_4_ai_depth_0", "[board_3]")
{
	ceg::BitBoard test_board = ceg::BitBoard(test_board_4_str);
	ceg::Move move = engine.get_ai_move(test_board, true, 0);

	REQUIRE(move.to_x == 4);
	REQUIRE(move.to_y == 1);
}

TEST_CASE("Test_board_4_ai_depth_1", "[board_3]")
{
	ceg::BitBoard test_board = ceg::BitBoard(test_board_4_str);
	ceg::Move move = engine.get_ai_move(test_board, true, 1);

	REQUIRE(move.to_x == 2);
	REQUIRE(move.to_y == 1);
}