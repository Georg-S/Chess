#pragma once
#include <cassert>
#include "Board.h"

inline bool is_occupied(uint32_t field);
bool is_field_occupied(const Board& board, int x, int y);
PieceColor get_piece_color(uint32_t piece);
PieceColor get_piece_color(const Board& board, int x, int y);
uint32_t get_piece_type_value(uint32_t piece);
bool is_move_valid(const Board& board, const Move& move);
void make_move(Board& board, Move& move);
bool has_pawn_reached_end_of_board(const Board& board);
PieceColor get_next_player(PieceColor player);
bool is_game_over(const Board& board, PieceColor color);