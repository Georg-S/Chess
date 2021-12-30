#pragma once
#include <ChessEngine.h>
#include <BitBoard.h>

struct RenderInformation
{
	RenderInformation(const ceg::BitBoard& board, int selectedX = -1, int selectedY = -1, int mouseX = 0, int mouseY = 0,
		ceg::Move previousMove = ceg::Move{ -1, -1, -1, -1 })
	{
		this->board = board;
		this->selectedPieceX = selectedX;
		this->selectedPieceY = selectedY;
		this->mousePositionX = mouseX;
		this->mousePositionY = mouseY;
		this->previousMove = previousMove;
		this->check_mate = false;
		this->stale_mate = false;
	}

	RenderInformation(const ceg::BitBoard& board, ceg::Move previousMove)
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

	ceg::BitBoard board;
	int selectedPieceX;
	int selectedPieceY;
	int mousePositionX;
	int mousePositionY;
	ceg::Move previousMove;
	bool check_mate;
	bool stale_mate;
};
