#include "Board.h"

ceg::BitBoard::BitBoard(const std::string& FEN_pieces_str)
{
	set_board(FEN_pieces_str);
}

void ceg::BitBoard::print_board_to_console()
{
	for (int y = 0; y < ceg::board_height; y++)
	{
		for (int x = 0; x < ceg::board_width; x++)
		{
			std::cout << get_field_char(x, y) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void ceg::BitBoard::set_board(const std::string& FEN_pieces_str)
{
	auto splitted = ceg::string_split(FEN_pieces_str, "/");
	assert(splitted.size() == 8);

	for (int y = 0; y < ceg::board_height; y++)
	{
		int x_index = 0;
		for (char c : splitted[y])
		{
			if (ceg::is_number(c))
			{
				x_index += c - '0';
				continue;
			}

			set_piece_by_FEN_char(c, x_index, y);
			x_index++;
		}
	}
	update_occupied();
}

void ceg::BitBoard::update_occupied()
{
	black_occupied = black_bishops | black_king | black_knights | black_pawns | black_queen | black_rooks;
	white_occupied = white_bishops | white_king | white_knights | white_pawns | white_queen | white_rooks;
	occupied = black_occupied | white_occupied;
}

void ceg::BitBoard::set_bit(uint64_t& num, int x, int y)
{
	ceg::set_bit(num, x + y * ceg::board_width);
}

bool ceg::BitBoard::is_bit_set(uint64_t num, int x, int y)
{
	return ceg::is_bit_set(num, x + y * ceg::board_width);
}

bool ceg::BitBoard::is_occupied(int x, int y)
{
	return is_bit_set(occupied, x, y);
}

char ceg::BitBoard::get_field_char(int x, int y)
{
	if (!is_occupied(x, y))
		return '-';

	return get_FEN_char(x, y);
}

char ceg::BitBoard::get_FEN_char(int x, int y)
{
	if (is_bit_set(black_pawns, x, y)) return 'p';
	if (is_bit_set(white_pawns, x, y)) return 'P';
	if (is_bit_set(black_bishops, x, y)) return 'b';
	if (is_bit_set(white_bishops, x, y)) return 'B';
	if (is_bit_set(black_knights, x, y)) return 'n';
	if (is_bit_set(white_knights, x, y)) return 'N';
	if (is_bit_set(black_rooks, x, y)) return 'r';
	if (is_bit_set(white_rooks, x, y)) return 'R';
	if (is_bit_set(black_queen, x, y)) return 'q';
	if (is_bit_set(white_queen, x, y)) return 'Q';
	if (is_bit_set(black_king, x, y)) return 'k';
	if (is_bit_set(white_king, x, y)) return 'K';
	assert(!"Couldn't get FEN char, no piece set at position");
	return ' ';
}

void ceg::BitBoard::set_piece_by_FEN_char(char c, int x, int y)
{
	bool black = islower(c);
	c = tolower(c);
	switch (c)
	{
	case 'p':
		if (black) 
			set_bit(black_pawns, x, y);
		else 
			set_bit(white_pawns, x, y);

		break;
	case 'n':
		if (black)
			set_bit(black_knights, x, y);
		else
			set_bit(white_knights, x, y);
		break;
	case 'b':
		if (black)
			set_bit(black_bishops, x, y);
		else
			set_bit(white_bishops, x, y);
		break;
	case 'r':
		if (black)
			set_bit(black_rooks, x, y);
		else
			set_bit(white_rooks, x, y);
		break;
	case 'q':
		if (black)
			set_bit(black_queen, x, y);
		else
			set_bit(white_queen, x, y);
		break;
	case 'k':
		if (black)
			set_bit(black_king, x, y);
		else
			set_bit(white_king, x, y);
		break;
	default:
		assert(!"Invalid character for FEN string");
		return;
	}
}
