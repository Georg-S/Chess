#pragma once
#include <vector>
#include <set>
#include <string>
#include <map>
#include "NegamaxAI.h"
#include "Utility.h"
#include "MoveGenerator.h"

namespace ceg
{
	struct Move
	{
		Move() = default;
		Move(int from_x, int from_y, int to_x, int to_y) : from_x(from_x), from_y(from_y), to_x(to_x), to_y(to_y) {};
		Move(const ceg::InternalMove& move)
		{
			from_x = move.from % 8;
			from_y = move.from / 8;
			to_x = move.to % 8;
			to_y = move.to / 8;
		}

		int from_x = 0;
		int from_y = 0;
		int to_x = 0;
		int to_y = 0;
	};

	enum class PieceColor { BLACK, WHITE };
	enum class Piece { PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING };

	class ChessEngine
	{
	public:
		ChessEngine();
		static PieceColor get_next_player(PieceColor color);
		std::vector<ceg::Move> get_all_possible_moves(const std::string& FEN_str);
		std::vector<ceg::Move> get_all_possible_moves_for_piece(const ceg::BitBoard& board, int piece_x, int piece_y);
		ceg::Move get_ai_move(const ceg::BitBoard& board, bool current_player_black, int depth);
		ceg::Move get_ai_move(const ceg::BitBoard& board, PieceColor color, int depth = 6);
		void make_move(ceg::BitBoard& board, ceg::Move move);
		void make_move_with_auto_promo(ceg::BitBoard& board, ceg::Move move);
		bool is_move_valid(const ceg::BitBoard& board, const ceg::Move& move);
		bool has_pawn_reached_end_of_board(ceg::BitBoard& board);
		bool is_game_over(const ceg::BitBoard& board, PieceColor color);
		bool is_field_occupied(const ceg::BitBoard& board, int x, int y);
		PieceColor get_piece_color(const ceg::BitBoard& board, int x, int y);
		void set_piece(ceg::BitBoard& board, Piece piece, PieceColor color, int x, int y);
		bool is_check_mate(ceg::BitBoard& board, PieceColor color);
		bool is_stale_mate(ceg::BitBoard& board, PieceColor color);

		uint64_t perft(const std::string& FEN_str, int depth);
		std::set<std::string> perft_get_set(const std::string& FEN_str, int depth);
		std::map<std::string, int> perft_get_map(const std::string& FEN_str, int depth);
	private:
		bool to_bool(ceg::PieceColor color);
		ceg::InternalMove convert_to_internal(const ceg::Move& move);
		uint64_t perft(const std::string& FEN_str, int depth, std::set<std::string>* out_set, std::map<std::string, int>* out_map);
		uint64_t perft(const ceg::BitBoard& board, bool current_player_black, int depth, std::set<std::string>* out_set, std::map<std::string, int>* out_map);

		std::unique_ptr<ceg::MoveGenerator> move_generator = nullptr;
		std::unique_ptr<NegamaxAI> ai = nullptr;
	};
}