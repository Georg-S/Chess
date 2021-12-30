#pragma once
#include <string>
#include <ChessEngine.h>
#include "SDL/Mouse.h"
#include "SDL/SDLButton.h"
#include "SDL/SDLHandler.h"
#include "Chess/Constant.h"

class PlayerColorSelection
{
public:
	PlayerColorSelection(SDLHandler* sdlHandler);
	void createColorSelection();
	bool color_selected() const;
	ceg::PieceColor getSelectedColor();
	void update();
	void destroy();

private:
	SDLHandler* sdlHandler;
	std::shared_ptr<RenderingElement> header;
	SDLButton* whiteButton;
	SDLButton* blackButton;
	Mouse mouse;

	const std::string headerPath = "Images/PlayerColorSelection/Header.png";
	const std::string blackPath = "Images/PlayerColorSelection/Black.png";
	const std::string whitePath = "Images/PlayerColorSelection/White.png";
};
