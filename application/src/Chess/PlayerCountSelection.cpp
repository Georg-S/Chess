#include "Chess/PlayerCountSelection.h"

PlayerCountSelection::PlayerCountSelection(SDLHandler* sdlHandler)
	: sdlHandler(sdlHandler)
{
}

void PlayerCountSelection::createPlayerSelection()
{
	int xPosition = 0;
	int yPosition = 0;
	yPosition += window_height / 2;
	xPosition += window_width / 2;
	onePlayer = new SDLButton(sdlHandler, 0, yPosition, window_width /2, window_height / 2, onePlayerUnselectedPath, onePlayerSelectedPath);
	twoPlayer = new SDLButton(sdlHandler, xPosition, yPosition, window_width / 2, window_height / 2, twoPlayerUnselectedPath, twoPlayerSelectedPath);
}

void PlayerCountSelection::update()
{
	sdlHandler->clear();
	mouse.update();
	sdlHandler->createAndPushBackRenderElement(headerPath, 0, 0, window_width, window_height / 2);
	onePlayer->updateButton(mouse.getMousePositionX(), mouse.getMousePositionY(), mouse.isNewLeftClick());
	twoPlayer->updateButton(mouse.getMousePositionX(), mouse.getMousePositionY(), mouse.isNewLeftClick());
	sdlHandler->update();
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
	sdlHandler->clear();
}
