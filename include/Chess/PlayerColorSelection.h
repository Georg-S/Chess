#pragma once
#include <string>
#include "SDL/Mouse.h"
#include "SDL/SDLButton.h"
#include "SDL/SDLHandler.h"
#include "Chess/Constant.h"
#include "Board.h"

class PlayerColorSelection
{
public:
	PlayerColorSelection(SDLHandler* sdlHandler);
	void createColorSelection();
	PieceColor getSelectedColor();
	void destroy();

private:
	void update();
	SDLHandler* sdlHandler;
	std::shared_ptr<RenderingElement> header;
	SDLButton* whiteButton;
	SDLButton* blackButton;
	Mouse mouse;

	const std::string headerPath = "Images/PlayerColorSelection/Header.png";
	const std::string blackPath = "Images/PlayerColorSelection/Black.png";
	const std::string whitePath = "Images/PlayerColorSelection/White.png";
};
