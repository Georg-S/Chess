#pragma once
#include "Board.h"

struct RenderInformation
{
	RenderInformation(Board& board, int selectedX = -1, int selectedY = -1, int mouseX = 0, int mouseY = 0,
		Move previousMove = Move{ -1, -1, -1, -1 })
	{
		this->board = board;
		this->selectedPieceX = selectedX;
		this->selectedPieceY = selectedY;
		this->mousePositionX = mouseX;
		this->mousePositionY = mouseY;
		this->previousMove = previousMove;
		this->check_mate = false;
		this->stale_mate = false;;
	}

	RenderInformation(const Board& board, Move previousMove)
	{
		this->board = board;
		this->previousMove = previousMove;

		this->selectedPieceX = -1;
		this->selectedPieceY = -1;
		this->mousePositionX = 0;
		this->mousePositionY = 0;
		this->check_mate = false;
		this->stale_mate = false;;
	}

	Board board;
	int selectedPieceX;
	int selectedPieceY;
	int mousePositionX;
	int mousePositionY;
	Move previousMove;
	bool check_mate;
	bool stale_mate;
};
