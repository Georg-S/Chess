#pragma once
#include <cassert>
#include <algorithm>
#include <vector>
#include "Board.h"
#include "Chess/Pieces/King.h"
#include "Chess/Pieces/Queen.h"
#include "Chess/Pieces/Rook.h"
#include "Chess/Pieces/Bishop.h"
#include "Chess/Pieces/Knight.h"
#include "Chess/Pieces/Pawn.h"

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
void reset_en_passant_direction(Board& board);
void make_move(Board& board, const Move& move);
void make_move_with_automatic_promotion(Board& board, const Move& move);
void move_piece_to_position(Board& board, const Move& move);
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
std::pair<int, int> get_king_pos(const Board& board, PieceColor color);
std::pair<int, int> get_distance(const Move& move);
void get_all_possible_moves_for_piece(const Board& board, std::vector<Move>& out_vec, int x, int y);
std::vector<Move> get_all_possible_moves(const Board& board, PieceColor color);
bool any_move_possible_for_piece(const Board& board, int x, int y);
bool any_move_possible(const Board& board, PieceColor color);
uint64_t perft(const Board& board, PieceColor, int depth);