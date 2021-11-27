#pragma once
#include <memory>
#include "GameLogic.h"
#include "SDL/SDLHandler.h"
#include "Board.h"
#include "RenderInformation.h"

class Renderer
{
public:
	Renderer();
	void render(const RenderInformation& renderInfo);
	//		void renderPromotionSelection(PieceColor color);
//	int getWindowWidth();
//	int getWindowHeight();
	void updateQuit();
	bool isQuit();
	void quit();

private:
	void renderChessBoard();
	void renderPieces(const Board& board);
//	void renderPiecesWithSelectedOnMousePosition(const RenderInformation& renderInfo);
//	void renderPreviousMove(const Move& previousMove);
	void renderPiece(const Board& board, int x, int y);
//	void renderPieceOnMousePosition(Piece* piece, int mouseX, int mouseY);
	std::string get_color_string(uint32_t piece) const;
	std::string get_piece_type_string(uint32_t piece) const;

	const int windowWidth = 800;
	const int windowHeight = 800;
	int pieceWidth;
	int pieceHeight;
	std::unique_ptr<SDLHandler> sdlHandler;
};
