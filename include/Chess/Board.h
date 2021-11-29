#pragma once
#include <cstdint>

constexpr int board_width = 8;
constexpr int board_height = 8;

constexpr uint32_t occupied_bit =				0b1;
constexpr uint32_t color_black_bit =			0b10;
constexpr uint32_t moved_bit =					0b100;
constexpr uint32_t king_bit =					0b1000;
constexpr uint32_t queen_bit =					0b10000;
constexpr uint32_t rook_bit =					0b100000;
constexpr uint32_t bishop_bit =					0b1000000;
constexpr uint32_t knight_bit =					0b10000000;
constexpr uint32_t pawn_bit =					0b100000000;
constexpr uint32_t en_paasant_x_negative_bit =	0b1000000000;
constexpr uint32_t en_passant_x_positive_bit =	0b10000000000;

constexpr uint32_t piece_bit_mask = king_bit | queen_bit | rook_bit | bishop_bit | knight_bit | pawn_bit;
constexpr uint32_t en_passant_clear_mask = ~(en_passant_x_positive_bit | en_paasant_x_negative_bit);

struct Move
{
	int fromX;
	int fromY;
	int toX;
	int toY;
};

enum class PieceColor
{
	UNDEFINED = 0,
	BLACK = 1,
	WHITE = 2
};

class Board 
{
public:
	void init_board();
	uint32_t* operator[](int index) const;
private:
	void empty_board();
	void init_white_site();
	void init_black_site();

	uint32_t board[board_width][board_height]{};
};
