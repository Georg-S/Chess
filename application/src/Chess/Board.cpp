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

static char get_fen_piece_char(uint64_t piece)
{
	switch (piece)
	{
	case pawn_bit:		return 'P';
	case knight_bit:	return 'N';
	case bishop_bit:	return 'B';
	case rook_bit:		return 'R';
	case queen_bit:		return 'Q';
	case king_bit:		return 'K';
	default:			assert(0);
	}
	return 0;
}

static char get_fen_char(uint64_t piece)
{
	uint32_t val = piece & piece_bit_mask;
	char piece_char = get_fen_piece_char(val);
	if (piece & color_black_bit)
		piece_char = tolower(piece_char);

	return piece_char;
}

std::string Board::to_FEN_str()
{
	std::string result = "";

	for (int y = 0; y < 8; y++)
	{
		int counter = 0;
		for (int x = 0; x < 8; x++)
		{
			if (!(board[x][y]))
			{
				counter++;
				continue;
			}

			if (counter != 0)
			{
				result += std::to_string(counter);
				counter = 0;
			}

			char fen_c = get_fen_char(board[x][y]);
			result += fen_c;
		}

		if (counter != 0)
		{
			result += std::to_string(counter);
			counter = 0;
		}

		if (y != 7)
			result += "/";
	}
	return result;
}

uint32_t* Board::operator[](int index) const
{
	return (uint32_t*)board[index];
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
