#include "Chess/Board.h"

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
	board[0][7] = rook | field_is_occupied;
	board[7][7] = rook | field_is_occupied;

	board[1][7] = knight | field_is_occupied;
	board[6][7] = knight | field_is_occupied;

	board[2][7] = bishop | field_is_occupied;
	board[5][7] = bishop | field_is_occupied;

	board[3][7] = queen | field_is_occupied;
	board[4][7] = king | field_is_occupied;

	for (int i = 0; i < 8; i++)
		board[i][6] = pawn | field_is_occupied;
}

void Board::init_black_site()
{
	board[0][0] = rook | field_is_occupied | color_is_black;
	board[7][0] = rook | field_is_occupied | color_is_black;

	board[1][0] = knight | field_is_occupied | color_is_black;
	board[6][0] = knight | field_is_occupied | color_is_black;

	board[2][0] = bishop | field_is_occupied | color_is_black;
	board[5][0] = bishop | field_is_occupied | color_is_black;

	board[3][0] = queen | field_is_occupied | color_is_black;
	board[4][0] = king | field_is_occupied | color_is_black;

	for (int i = 0; i < 8; i++)
		board[i][1] = pawn | field_is_occupied | color_is_black;
}
