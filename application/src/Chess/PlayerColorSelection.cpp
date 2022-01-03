#include "Chess/PlayerColorSelection.h"

PlayerColorSelection::PlayerColorSelection(SDLHandler* sdlHandler)
{
	this->sdlHandler = sdlHandler;
}

void PlayerColorSelection::createColorSelection()
{
	int xPosition = 0;
	int yPosition = 0;
	header = sdlHandler->createAndPushBackRenderElement(headerPath, 0, 0, window_width, window_height / 2);
	yPosition += window_height / 2;
	whiteButton = new SDLButton(sdlHandler, 0, yPosition, window_width / 2, window_height / 2, whitePath, whitePath);
	xPosition += window_width / 2;
	blackButton = new SDLButton(sdlHandler, xPosition, yPosition, window_width / 2, window_height / 2, blackPath, blackPath);
}

bool PlayerColorSelection::color_selected() const
{
	return whiteButton->wasClicked() || blackButton->wasClicked();
}

void PlayerColorSelection::update()
{
	sdlHandler->update();
	mouse.update();
	whiteButton->updateButton(mouse.getMousePositionX(), mouse.getMousePositionY(), mouse.isNewLeftClick());
	blackButton->updateButton(mouse.getMousePositionX(), mouse.getMousePositionY(), mouse.isNewLeftClick());
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
	sdlHandler->deleteRenderingElementAndTexture(header);
	whiteButton->destroy();
	blackButton->destroy();
}
