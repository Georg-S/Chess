#pragma once
#include <memory>
#include "Board.h"
#include "Renderer.h"

class Chess 
{
public:
	Chess();

	void play_vs_AI();

private:
	std::unique_ptr<Renderer> renderer;
};