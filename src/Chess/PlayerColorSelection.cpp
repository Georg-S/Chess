#include "Chess/PlayerColorSelection.h"

/*
ColorSelection::ColorSelection(SDLHandler* sdlHandler, int windowWidth, int windowHeight)
{
	this->sdlHandler = sdlHandler;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}

ColorSelection::~ColorSelection()
{
}

void ColorSelection::createColorSelection()
{
	int xPosition = 0;
	int yPosition = 0;
	header = sdlHandler->createAndPushRenderElement(headerPath, 0, 0, windowWidth, windowHeight / 2);
	yPosition += windowHeight / 2;
	whiteButton = new SDLButton(sdlHandler, 0, yPosition, windowWidth / 2, windowHeight / 2, whitePath, whitePath);
	xPosition += windowWidth / 2;
	blackButton = new SDLButton(sdlHandler, xPosition, yPosition, windowWidth / 2, windowHeight / 2, blackPath, blackPath);
}

void ColorSelection::update(const int & mousePositionX, const int & mousePositionY, const bool & clicked)
{
	whiteButton->updateButton(mousePositionX, mousePositionY, clicked);
	blackButton->updateButton(mousePositionX, mousePositionY, clicked);
}

COLOR ColorSelection::getSelectedColor()
{
	if (whiteButton->wasClicked())
		return WHITE;
	if (blackButton->wasClicked())
		return BLACK;
	return NONE;
}

void ColorSelection::destroy()
{
	sdlHandler->deleteRenderingElement(header);
	whiteButton->destroy();
	blackButton->destroy();
}
*/