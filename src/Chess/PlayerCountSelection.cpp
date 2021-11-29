#include "Chess/PlayerCountSelection.h"

PlayerCountSelection::PlayerCountSelection(SDLHandler* sdlHandler)
{
	this->sdlHandler = sdlHandler;
}

void PlayerCountSelection::createPlayerSelection()
{
	int xPosition = 0;
	int yPosition = 0;
	header = sdlHandler->createAndPushBackRenderElement(headerPath, 0, 0, window_width, window_height / 2);
	yPosition += window_height / 2;
	onePlayer = new SDLButton(sdlHandler, 0, yPosition, window_width /2, window_height / 2, onePlayerUnselectedPath, onePlayerSelectedPath);
	xPosition += window_width / 2;
	twoPlayer = new SDLButton(sdlHandler, xPosition, yPosition, window_width / 2, window_height / 2, twoPlayerUnselectedPath, twoPlayerSelectedPath);
}

void PlayerCountSelection::update()
{
	sdlHandler->update();
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
