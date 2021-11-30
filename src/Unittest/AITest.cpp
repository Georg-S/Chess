#include "Unittest/catch_amalgamated.hpp"
#include "Chess/Board.h"
#include "Chess//Renderer.h"
#include "Chess/NegamaxAI.h"

static Board init_test_board_1() 
{
    Board board;
    board.init_empty_board();

    board[0][6] = pawn_bit | occupied_bit;
    board[1][6] = pawn_bit | occupied_bit;
    board[2][6] = pawn_bit | occupied_bit;
    board[0][7] = king_bit | occupied_bit;

    board[0][0] = king_bit | color_black_bit | occupied_bit;
    board[3][0] = queen_bit | color_black_bit | occupied_bit;

    return board;
}

Board init_test_board_2()
{
    Board board;
    board.init_empty_board();

    board[0][6] = pawn_bit | occupied_bit;
    board[1][6] = pawn_bit | occupied_bit;
    board[2][6] = pawn_bit | occupied_bit;
    board[0][7] = king_bit | occupied_bit;
    board[6][7] = queen_bit | occupied_bit;

    board[0][0] = king_bit | color_black_bit | occupied_bit;
    board[3][4] = queen_bit | color_black_bit | occupied_bit;

    return board;
}

static void output_board(const Board& board) 
{
    Renderer renderer;
    renderer.render_board(board);
    getchar();
}

static Move get_move_from_ai(const Board& board, PieceColor color, int depth) 
{
    NegamaxAI ai;
    return ai.get_move(board, PieceColor::BLACK, depth);
}

TEST_CASE("Test_board_1_ai_depth_0", "[board_1]")
{
    Board test_board_1 = init_test_board_1();
    Move move = get_move_from_ai(test_board_1, PieceColor::BLACK, 0);

    REQUIRE(move.toX == 3);
    REQUIRE(move.toY == 7);
}

TEST_CASE("Test_board_1_ai_depth_1", "[board_1]")
{
    Board test_board_1 = init_test_board_1();
    Move move = get_move_from_ai(test_board_1, PieceColor::BLACK, 1);

    REQUIRE(move.toX == 3);
    REQUIRE(move.toY == 7);
}

TEST_CASE("Test_board_1_ai_depth_2", "[board_1]")
{
    Board test_board_1 = init_test_board_1();
    Move move = get_move_from_ai(test_board_1, PieceColor::BLACK, 2);

    REQUIRE(move.toX == 3);
    REQUIRE(move.toY == 7);
}

TEST_CASE("Test_board_1_ai_depth_3", "[board_1]")
{
    Board test_board_1 = init_test_board_1();
    Move move = get_move_from_ai(test_board_1, PieceColor::BLACK, 3);

    REQUIRE(move.toX == 3);
    REQUIRE(move.toY == 7);
}

TEST_CASE("Test_board_2_ai_depth_0", "[board_2]")
{
    Board test_board_2 = init_test_board_2();
    Move move = get_move_from_ai(test_board_2, PieceColor::BLACK, 0);

    REQUIRE(move.toX == 6);
    REQUIRE(move.toY == 7);
}

TEST_CASE("Test_board_2_ai_depth_1", "[board_2]")
{
    Board test_board_2 = init_test_board_2();
    Move move = get_move_from_ai(test_board_2, PieceColor::BLACK, 1);

    REQUIRE(move.toX == 6);
    REQUIRE(move.toY == 7);
}

TEST_CASE("Test_board_2_ai_depth_2", "[board_2]")
{
    Board test_board_2 = init_test_board_2();
    Move move = get_move_from_ai(test_board_2, PieceColor::BLACK, 2);

    REQUIRE(move.toX == 6);
    REQUIRE(move.toY == 7);
}
