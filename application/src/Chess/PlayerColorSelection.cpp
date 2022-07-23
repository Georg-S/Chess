#include "Chess/PlayerColorSelection.h"

PlayerColorSelection::PlayerColorSelection(SDLHandler* sdlHandler)
	: sdlHandler (sdlHandler)
{
}

void PlayerColorSelection::createColorSelection()
{
	int xPosition = 0;
	int yPosition = 0;
	yPosition += window_height / 2;
	xPosition += window_width / 2;
	whiteButton = new SDLButton(sdlHandler, 0, yPosition, window_width / 2, window_height / 2, whitePath, whitePath);
	blackButton = new SDLButton(sdlHandler, xPosition, yPosition, window_width / 2, window_height / 2, blackPath, blackPath);
}

bool PlayerColorSelection::color_selected() const
{
	return whiteButton->wasClicked() || blackButton->wasClicked();
}

void PlayerColorSelection::update()
{
	sdlHandler->clear();
	mouse.update();
	sdlHandler->createAndPushBackRenderElement(headerPath, 0, 0, window_width, window_height / 2);
	whiteButton->updateButton(mouse.getMousePositionX(), mouse.getMousePositionY(), mouse.isNewLeftClick());
	blackButton->updateButton(mouse.getMousePositionX(), mouse.getMousePositionY(), mouse.isNewLeftClick());
	sdlHandler->update();
}

ceg::PieceColor PlayerColorSelection::getSelectedColor() const
{
	if (whiteButton->wasClicked())
		return ceg::PieceColor::WHITE;
	if (blackButton->wasClicked())
		return ceg::PieceColor::BLACK;

	return ceg::PieceColor::WHITE;
}

void PlayerColorSelection::destroy()
{
	sdlHandler->clear();
}
