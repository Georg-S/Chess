#pragma once
#include <iostream>
#include <string>
#include <assert.h>
#include "Utility.h"

namespace ceg
{
	constexpr int board_width = 8;
	constexpr int board_height = 8;

	class BitBoard
	{
		struct Pieces
		{
			uint64_t pawns = 0;
			uint64_t bishops = 0;
			uint64_t knights = 0;
			uint64_t rooks = 0;
			uint64_t queens = 0;
			uint64_t king = 0;
			uint64_t occupied = 0;
		};

	public:
		BitBoard() = default;
		BitBoard(const std::string& FEN_pieces_str, const std::string& FEN_castling_str = "", const std::string& FEN_en_passant_str = "");

		void clear_bit_for_color(bool black, int bit_index);
		void clear_bit_for_pieces(Pieces* pieces, int bit_index);
		uint64_t* get_ptr_to_piece(bool black, int bit_index);
		uint64_t* get_ptr_to_piece(Pieces& pieces, int bit_index);
		void print_board_to_console();
		void set_board(const std::string& FEN_pieces_str, const std::string& FEN_castling_str = "", const std::string& FEN_en_passant_str = "");

		Pieces white_pieces;
		Pieces black_pieces;

		uint64_t en_passant_mask = 0;
		uint64_t castling_mask = 0;
		uint64_t occupied = 0;
	private:
		void set_en_passant(const std::string& FEN_str);
		void set_castling(const std::string& FEN_castling_str);
		void update_occupied();
		bool is_bit_set(uint64_t num, int x, int y);
		bool is_occupied(int x, int y);
		char get_field_char(int x, int y);
		char get_FEN_char(int x, int y);
		void set_piece_by_FEN_char(char c, int x, int y);
	};
}