#include "Chess/Board.h"

void Board::init_empty_board()
{
	empty_board();
}

void Board::init_board()
{
	empty_board();
	init_white_site();
	init_black_site();
}

uint32_t* Board::operator[](int index) const
{
	return (uint32_t *)board[index];
}

void Board::empty_board()
{
	for (int x = 0; x < board_width; x++)
		for (int y = 0; y < board_height; y++)
			board[x][y] = 0;
}

void Board::init_white_site()
{
	board[0][7] = rook_bit | occupied_bit;
	board[7][7] = rook_bit | occupied_bit;

	board[1][7] = knight_bit | occupied_bit;
	board[6][7] = knight_bit | occupied_bit;

	board[2][7] = bishop_bit | occupied_bit;
	board[5][7] = bishop_bit | occupied_bit;

	board[3][7] = queen_bit | occupied_bit;
	board[4][7] = king_bit | occupied_bit;

	for (int i = 0; i < 8; i++)
		board[i][6] = pawn_bit | occupied_bit;
}

void Board::init_black_site()
{
	board[0][0] = rook_bit | occupied_bit | color_black_bit;
	board[7][0] = rook_bit | occupied_bit | color_black_bit;

	board[1][0] = knight_bit | occupied_bit | color_black_bit;
	board[6][0] = knight_bit | occupied_bit | color_black_bit;

	board[2][0] = bishop_bit | occupied_bit | color_black_bit;
	board[5][0] = bishop_bit | occupied_bit | color_black_bit;

	board[3][0] = queen_bit | occupied_bit | color_black_bit;
	board[4][0] = king_bit | occupied_bit | color_black_bit;

	for (int i = 0; i < 8; i++)
		board[i][1] = pawn_bit | occupied_bit | color_black_bit;
}
