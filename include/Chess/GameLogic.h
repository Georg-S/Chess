#pragma once
#include <cassert>
#include <algorithm>
#include "Board.h"

inline bool is_occupied(uint32_t field);
inline bool has_moved(uint32_t field);
bool is_field_occupied(const Board& board, int x, int y);
bool has_moved(const Board& board, int x, int y);
int get_en_passant_direction(const Board& board, int x, int y);
PieceColor get_piece_color(uint32_t piece);
PieceColor get_piece_color(const Board& board, int x, int y);
uint32_t get_piece_type_value(uint32_t piece);
bool pieces_have_different_color(const Board& board, const Move& move);
bool is_move_valid(const Board& board, const Move& move);
void make_move(Board& board, Move& move);
bool has_pawn_reached_end_of_board(const Board& board);
PieceColor get_next_player(PieceColor player);
bool is_game_over(const Board& board, PieceColor color);
bool is_check(const Board& board, PieceColor color);
bool is_check(const Board& board, int king_x, int king_y);
bool is_check_mate(const Board& board, PieceColor color);
bool is_stale_mate(const Board& board, PieceColor color);
bool direct_move_possible(const Board& board, const Move& move, int dir_x, int dir_y);
bool direct_move_possible(const Board& board, const Move& move);
int get_x_direction(const Move& move);
int get_y_direction(const Move& move);
std::pair<int,int> get_direction(const Move& move);
int get_x_distance(const Move& move);
int get_y_distance(const Move& move);
std::pair<int, int> get_distance(const Move& move);