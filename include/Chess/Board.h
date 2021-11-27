#pragma once
#include <cstdint>

constexpr int board_width = 8;
constexpr int board_height = 8;

constexpr uint32_t field_is_occupied =		0b1;
constexpr uint32_t color_is_black =			0b10;
constexpr uint32_t moved =					0b100;
constexpr uint32_t king =					0b1000;
constexpr uint32_t queen =					0b10000;
constexpr uint32_t rook =					0b100000;
constexpr uint32_t bishop =					0b1000000;
constexpr uint32_t knight =					0b10000000;
constexpr uint32_t pawn =					0b100000000;
constexpr uint32_t en_paasant_x_negative =	0b1000000000;
constexpr uint32_t en_passant_x_positive =	0b10000000000;

constexpr uint32_t piece_mask = king | queen | rook | bishop | knight | pawn;

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

