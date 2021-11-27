#pragma once
#include <cassert>
#include "Board.h"

inline bool is_occupied(uint32_t field);
bool is_field_occupied(Board board, int x, int y);
PieceColor get_piece_color(uint32_t piece);
uint32_t get_piece_type_value(uint32_t piece);