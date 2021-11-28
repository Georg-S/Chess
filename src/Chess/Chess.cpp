#include "Chess/Chess.h"

Chess::Chess()
{
	renderer = std::make_unique<Renderer>();
	board.init_board();
}

void Chess::game_loop()
{
	while (!renderer->update_quit())
	{
//		renderer->render(RenderInformation{ board, previous_move });
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
	renderer->render(RenderInformation{ board, previous_move });

	if (has_pawn_reached_end_of_board(board))
	{
		handle_promo_selection(board, move.toX, move.toY);
	}
	current_player = get_next_player(current_player);

	if (is_game_over(board, current_player))
		handle_game_over();
}

Move Chess::get_human_move()
{
	mouse.update();
	Move move = Move{ -1, -1, -1, -1 };
	RenderInformation renderInfo = RenderInformation(board);
	const bool piece_selected = (pending_move.fromX != -1) && (pending_move.fromY != -1);

	if (piece_selected)
	{
		renderInfo.selectedPieceX = pending_move.fromX;
		renderInfo.selectedPieceY = pending_move.fromY;
		renderInfo.mousePositionX = mouse.getMousePositionX();
		renderInfo.mousePositionY = mouse.getMousePositionY();
		renderInfo.previousMove = previous_move;
		renderer->render(renderInfo);
	}

	if (mouse.isRightPressed())
	{
		pending_move.fromX = -1;
		pending_move.fromY = -1;
		renderer->render(renderInfo);
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

		if (!is_move_valid(board, move))
			renderer->render(board);
	}

	return move;
}

bool Chess::is_valid_move(const Move& move)
{
	if(!is_valid_board_pos(move.fromX, move.fromY) || !is_valid_board_pos(move.toX, move.toY))
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
