#include "Unittest/catch_amalgamated.hpp"
#include "BitBoard.h"
#include "ChessEngine.h"
#include "MoveGenerator.h"
#include "ValueTables.h"

const std::string initial_board_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
const std::string perft_test_board_2 = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ";
const std::string perft_test_board_3 = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - ";
const std::string perft_test_board_4 = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1";
const std::string perft_test_board_5 = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8";
const std::string perft_test_board_6 = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10";
static ceg::ChessEngine engine = ceg::ChessEngine();


/*
TEST_CASE("perft_test_board_2_depth_3_test", "MoveGeneration")
{
	uint64_t perft_result = engine.perft(perft_test_board_2, 3);

	REQUIRE(perft_result == 97862);
}

TEST_CASE("perft_test_board_5_depth_1_test", "MoveGeneration")
{
	uint64_t perft_result = engine.perft(perft_test_board_5, 1);

	REQUIRE(perft_result == 44);
}



TEST_CASE("perft_test_board_5_depth_6_test", "MoveGeneration")
{
    ScopedTimer timer{};
    uint64_t perft_result = engine.perft(initial_board_FEN, 6);
}

TEST_CASE("perft_test_board_5_depth_7_test", "MoveGeneration")
{
    getchar();
}

TEST_CASE("flip_piece_tables", "MoveGeneration")
{
    int my_arr[64];
    copy(my_arr, white_king_end_game_table);

    flip_y(my_arr);

    print_values(my_arr);
}
*/

class ScopedTimer
{
public:
    ScopedTimer()
    {
        start_time = std::chrono::high_resolution_clock::now();
    }
    ~ScopedTimer()
    {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto dif = end_time - start_time;
        auto in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(dif);

        std::cout << "Time in seconds: " << (in_ms.count()) / 1000. << std::endl;
    }
private:
    std::chrono::steady_clock::time_point start_time;
};


