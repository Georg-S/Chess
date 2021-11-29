#include "Chess/Chess.h"

Chess::Chess()
{
	renderer = std::make_unique<Renderer>();
	board.init_board();
	render_info = std::make_unique<RenderInformation>(board);
}

void Chess::game_loop()
{
	while (!renderer->is_quit())
	{
		renderer->render(*render_info);
		if (player_count == 1)
			update_1_player_game();
		else
			update_2_player_game();
	}
}

void Chess::update_1_player_game()
{
}

void Chess::update_2_player_game()
{
	update_human_move();
}

void Chess::update_ai_move()
{
}

void Chess::update_human_move()
{
	Move move = get_human_move();
	if (!is_valid_move(move))
		return;

	make_move(board, move);
	previous_move = move;
	render_info = std::make_unique<RenderInformation>(board, previous_move);

	if (has_pawn_reached_end_of_board(board))
		handle_promo_selection(board, move.toX, move.toY);

	current_player = get_next_player(current_player);

	if (is_game_over(board, current_player))
		handle_game_over();
}

Move Chess::get_human_move()
{
	mouse.update();
	Move move = Move{ -1, -1, -1, -1 };
	render_info = std::make_unique<RenderInformation>(board, previous_move);
	const bool piece_selected = (pending_move.fromX != -1) && (pending_move.fromY != -1);

	if (piece_selected)
	{
		render_info->selectedPieceX = pending_move.fromX;
		render_info->selectedPieceY = pending_move.fromY;
		render_info->mousePositionX = mouse.getMousePositionX();
		render_info->mousePositionY = mouse.getMousePositionY();
		render_info->previousMove = previous_move;
	}

	if (mouse.isRightPressed())
	{
		pending_move.fromX = -1;
		pending_move.fromY = -1;
		return move;
	}

	if (!mouse.isNewLeftClick())
		return move;

	const int boardX = convert_mouse_position_x_to_board_position(mouse.getMousePositionX());
	const int boardY = convert_mouse_position_y_to_board_position(mouse.getMousePositionY());

	if (!is_valid_board_pos(boardX, boardY))
		return move;

	if (!piece_selected)
	{
		if (is_field_occupied(board, boardX, boardY) && (get_piece_color(board, boardX, boardY) == current_player))
		{
			pending_move.fromX = boardX;
			pending_move.fromY = boardY;
		}
	}
	else
	{
		move = Move{ pending_move.fromX, pending_move.fromY, boardX, boardY };
		pending_move.fromX = -1;
		pending_move.fromY = -1;
	}

	return move;
}

bool Chess::is_valid_move(const Move& move)
{
	if (!is_valid_board_pos(move.fromX, move.fromY) || !is_valid_board_pos(move.toX, move.toY))
		return false;
	if (!is_field_occupied(board, move.fromX, move.fromY))
		return false;

	return is_move_valid(board, move);
}

bool Chess::is_valid_board_pos(int x, int y)
{
	return (x >= 0) && (x < board_width) && (y >= 0) && (y < board_height);
}

void Chess::handle_promo_selection(Board& board, int posx, int posy)
{
	renderer->render_promotion_selection(current_player);

	bool validPieceSelected = false;

	while (!validPieceSelected)
	{
		mouse.update();

		if (!mouse.isNewLeftClick())
			continue;

		uint32_t piece = get_piece_from_promo_selection(mouse.getMousePositionX(), mouse.getMousePositionY());

		if (piece == 0)
			continue;

		board[posx][posy] = piece;
		validPieceSelected = true;
	}
}

uint32_t Chess::get_piece_from_promo_selection(int mouseX, int mouseY)
{
	int x = mouseX / (renderer->getWindowWidth() / 2);
	int y = mouseY / (renderer->getWindowHeight() / 2);

	uint32_t color = (current_player == PieceColor::BLACK) ? color_black_bit : 0;

	if (x == 0 && y == 0)
		return (queen_bit | color | moved_bit | occupied_bit);
	else if (x == 1 && y == 0)
		return (rook_bit | color | moved_bit | occupied_bit);
	else if (x == 0 && y == 1)
		return (knight_bit | color | moved_bit | occupied_bit);
	else if (x == 1 && y == 1)
		return (bishop_bit | color | moved_bit | occupied_bit);

	return 0;
}

void Chess::handle_game_over()
{
}

int Chess::convert_mouse_position_x_to_board_position(int mouse_x)
{
	return mouse_x / (renderer->getWindowWidth() / board_width);
}

int Chess::convert_mouse_position_y_to_board_position(int mouse_y)
{
	return mouse_y / (renderer->getWindowHeight() / board_height);
}
