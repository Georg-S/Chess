#include "Chess/PlayerCountSelection.h"

PlayerCountSelection::PlayerCountSelection(SDLHandler* sdlHandler, int windowWidth, int windowHeight)
{
	this->sdlHandler = sdlHandler;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}

void PlayerCountSelection::createPlayerSelection()
{
	int xPosition = 0;
	int yPosition = 0;
	header = sdlHandler->createAndPushBackRenderElement(headerPath, 0, 0, windowWidth, windowHeight / 2);
	yPosition += windowHeight / 2;
	onePlayer = new SDLButton(sdlHandler, 0, yPosition, windowWidth/2, windowHeight / 2, onePlayerUnselectedPath, onePlayerSelectedPath);
	xPosition += windowWidth / 2;
	twoPlayer = new SDLButton(sdlHandler, xPosition, yPosition, windowWidth / 2, windowHeight / 2, twoPlayerUnselectedPath, twoPlayerSelectedPath);
}

void PlayerCountSelection::update()
{
	sdlHandler->updateRendering();
	mouse.update();
	onePlayer->updateButton(mouse.getMousePositionX(), mouse.getMousePositionY(), mouse.isNewLeftClick());
	twoPlayer->updateButton(mouse.getMousePositionX(), mouse.getMousePositionY(), mouse.isNewLeftClick());
}

int PlayerCountSelection::getSelectedPlayerCount()
{
	update();
	if (onePlayer->wasClicked())
		return 1;
	if (twoPlayer->wasClicked())
		return 2;

	return -1;
}

void PlayerCountSelection::destroy()
{
	sdlHandler->deleteRenderingElementAndTexture(header);
	onePlayer->destroy();
	twoPlayer->destroy();
}
