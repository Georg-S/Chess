#include "Chess/Chess.h"

Chess::Chess()
{
	renderer = std::make_unique<Renderer>();
}

void Chess::play_vs_AI()
{
	Board board;
	board.init_board();

	while (!renderer->update_quit()) 
	{
		renderer->render(RenderInformation{board});
	}
}
