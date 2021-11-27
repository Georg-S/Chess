#include "Chess/Renderer.h"

Renderer::Renderer()
{
	sdl_handler = std::make_unique<SDLHandler>(window_width, window_height, true);
	piece_width = window_width / board_width;
	piece_height = window_height / board_height;
	sdl_handler->start("Chess");
}

void Renderer::render(const RenderInformation& renderInfo)
{
	sdl_handler->clear();
	render_chess_board();

	render_pieces(renderInfo.board);
	/*
	if (renderInfo.previousMove.fromX != -1)
		renderPreviousMove(renderInfo.previousMove);

	if (renderInfo.selectedPieceY == -1 || renderInfo.selectedPieceX == -1)
		renderPieces(renderInfo.board);
	else
		renderPiecesWithSelectedOnMousePosition(renderInfo);
	*/

	sdl_handler->updateRendering();
}

void Renderer::render_chess_board()
{
	sdl_handler->createAndPushBackRenderElement("Images/Board.png", 0, 0, window_width, window_height);
}

void Renderer::render_pieces(const Board& board)
{
	for (int x = 0; x < board_width; x++)
	{
		for (int y = 0; y < board_height; y++)
		{
			if (is_field_occupied(board, x, y))
				render_piece(board, x, y);
		}
	}
}

void Renderer::render_piece(const Board& board, int x, int y)
{
	auto piece = board[x][y];
	std::string fileString = "Images/" + get_piece_type_string(piece) + "_" + get_color_string(piece) + ".png";
	sdl_handler->createAndPushBackRenderElement(fileString, piece_width * x, piece_height * y, piece_width, piece_height);
}

std::string Renderer::get_color_string(uint32_t piece) const
{
	PieceColor piece_color = get_piece_color(piece);

	if (piece_color == PieceColor::WHITE)
		return "white";
	else if (piece_color == PieceColor::BLACK)
		return "black";
}

std::string Renderer::get_piece_type_string(uint32_t piece) const
{
	uint32_t piece_type = get_piece_type_value(piece);

	switch (piece_type)
	{
	case pawn:		return "Pawn";
	case knight:	return "Knight";
	case queen:		return "Queen";
	case king:		return "King";
	case bishop:	return "Bishop";
	case rook:		return "Rook";
	default: assert(0);
	}
}
/*
void Renderer::renderPiecesWithSelectedOnMousePosition(const RenderInformation& renderInfo)
{
	Piece* foreGroundPiece = nullptr;

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (x == renderInfo.selectedPieceX && y == renderInfo.selectedPieceY)
				foreGroundPiece = renderInfo.board.board[x][y];
			else if (renderInfo.board.board[x][y] != nullptr)
				renderPiece(renderInfo.board, x, y);
		}
	}
	renderPieceOnMousePosition(foreGroundPiece, renderInfo.mousePositionX, renderInfo.mousePositionY);
}

void Renderer::renderPreviousMove(const Move& previousMove)
{
	sdlHandler->createAndPushBackRenderElement("Images/Chess/PreviousMove.png", pieceWidth * previousMove.fromX, pieceHeight * previousMove.fromY
		, pieceWidth, pieceHeight);

	sdlHandler->createAndPushBackRenderElement("Images/Chess/PreviousMove.png", pieceWidth * previousMove.toX, pieceHeight * previousMove.toY
		, pieceWidth, pieceHeight);
}
*/


/*
int Renderer::getWindowWidth()
{
	return this->windowWidth;
}

int Renderer::getWindowHeight()
{
	return this->windowHeight;
}

void Renderer::renderPieceOnMousePosition(Piece* piece, int mouseX, int mouseY)
{
	std::string fileString = getFileString(piece);
	sdlHandler->createAndPushBackRenderElement(fileString, mouseX - (pieceWidth / 2), mouseY - (pieceHeight / 2), pieceWidth, pieceHeight);
}

void Renderer::renderPromotionSelection(PieceColor color)
{
	sdlHandler->clear();
	sdlHandler->createAndPushBackRenderElement("Images/Chess/background.png", 0, 0, windowWidth, windowHeight);

	std::string queenStr = getFileString('Q', color);
	std::string rookStr = getFileString('R', color);
	std::string knightStr = getFileString('H', color);
	std::string  bishopStr = getFileString('B', color);

	sdlHandler->createAndPushBackRenderElement(queenStr, 0, 0, windowWidth / 2, windowHeight / 2);
	sdlHandler->createAndPushBackRenderElement(rookStr, windowWidth / 2, 0, windowWidth / 2, windowHeight / 2);
	sdlHandler->createAndPushBackRenderElement(knightStr, 0, windowHeight / 2, windowWidth / 2, windowHeight / 2);
	sdlHandler->createAndPushBackRenderElement(bishopStr, windowWidth / 2, windowHeight / 2, windowWidth / 2, windowHeight / 2);

	sdlHandler->updateRendering();
}
*/

bool Renderer::update_quit()
{
	sdl_handler->updateQuit();
	if (sdl_handler->exit)
		sdl_handler->close();

	return sdl_handler->exit;
}

bool Renderer::is_quit()
{
	return sdl_handler->exit;
}

void Renderer::quit()
{
	sdl_handler->close();
}
