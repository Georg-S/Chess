#include "Chess/Chess.h"

Chess::Chess()
{
	renderer = std::make_unique<Renderer>();
}

void Chess::play_vs_AI()
{
	Board board;
	board.init_board();

	while (true) 
	{
		renderer->render(RenderInformation{board});
	}
}
