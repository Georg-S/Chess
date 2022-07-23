#include "SDL/SDLButton.h"

SDLButton::SDLButton(SDLHandler* sdlHandler, int x, int y, int width, int height, std::string unselectedFilePath, std::string selectedFilePath)
{
	this->sdlHandler = sdlHandler;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->unselectedFilePath = unselectedFilePath;
	this->selectedFilePath = selectedFilePath;
}

void SDLButton::updateButton(const int& mousePositionX, const int& mousePositionY, const bool& clicked)
{
	if (isMouseOverButton(mousePositionX, mousePositionY))
	{
		this->clicked = clicked;
		sdlHandler->createAndPushBackRenderElement(selectedFilePath, x, y, width, height);
	}
	else
	{
		sdlHandler->createAndPushBackRenderElement(unselectedFilePath, x, y, width, height);
	}
}

bool SDLButton::wasClicked()
{
	return clicked;
}

bool SDLButton::isMouseOverButton(const int& mousePositionX, const int& mousePositionY)
{
	if (mousePositionX >= this->x && mousePositionX <= this->x + this->width)
	{
		if (mousePositionY >= this->y && mousePositionY <= this->y + this->height)
			return true;
	}
	return false;
}
