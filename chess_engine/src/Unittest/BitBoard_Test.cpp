#include "Unittest/catch_amalgamated.hpp"
#include "BitBoard.h"

TEST_CASE("fen_pieces_string_test_1", "BitBoard")
{
	const std::string board_initial_str = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	ceg::BitBoard board = ceg::BitBoard(board_initial_str);

	REQUIRE(board_initial_str == board.getPiecesFENString());
}

TEST_CASE("fen_pieces_string_test_2", "BitBoard")
{
	const std::string board_initial_str = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R";
	ceg::BitBoard board = ceg::BitBoard(board_initial_str);

	REQUIRE(board_initial_str == board.getPiecesFENString());
}

TEST_CASE("fen_string_test_1", "BitBoard") 
{
	const std::string board_initial_str = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -";
	ceg::BitBoard board = ceg::BitBoard(board_initial_str);

	REQUIRE(board_initial_str == ceg::to_FEN_string(board, false));
}

TEST_CASE("fen_string_test_en_passant_1", "BitBoard")
{
	const std::string board_initial_str = "rnbqkbnr/ppp1ppp1/7p/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6";
	ceg::BitBoard board = ceg::BitBoard(board_initial_str);

	REQUIRE(board_initial_str == ceg::to_FEN_string(board, false));
}

TEST_CASE("fen_string_test_en_passant_2", "BitBoard")
{
	const std::string board_initial_str = "rnbqkbnr/pppp1ppp/8/8/3PpP2/P7/1PP1P1PP/RNBQKBNR b KQkq f3";
	ceg::BitBoard board = ceg::BitBoard(board_initial_str);

	REQUIRE(board_initial_str == ceg::to_FEN_string(board, true));
}

TEST_CASE("fen_string_test_en_passant_3", "BitBoard")
{
	const std::string board_initial_str = "rnbqkbnr/ppp1ppp1/7p/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6";
	ceg::BitBoard board = ceg::BitBoard(board_initial_str);

	REQUIRE(ceg::is_bit_set(board.en_passant_mask, 3, 2));
}

TEST_CASE("fen_string_test_castling", "BitBoard")
{
	const std::string board_initial_str = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w Kq -";
	ceg::BitBoard board = ceg::BitBoard(board_initial_str);

	REQUIRE(board_initial_str == ceg::to_FEN_string(board, false));
}
