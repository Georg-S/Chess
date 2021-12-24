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

	selected = sdlHandler->createAndPushBackRenderElement(selectedFilePath, x, y, width, height);
	unselected = sdlHandler->createAndPushBackRenderElement(unselectedFilePath, x, y, width, height);
	selected->render = false;
}

void SDLButton::updateButton(const int& mousePositionX, const int& mousePositionY, const bool& clicked)
{
	if (isMouseOverButton(mousePositionX, mousePositionY))
	{
		selected->render = true;
		unselected->render = false;
		this->clicked = clicked;
	}
	else
	{
		selected->render = false;
		unselected->render = true;
	}
}

bool SDLButton::wasClicked()
{
	return clicked;
}

void SDLButton::destroy()
{
	sdlHandler->deleteRenderingElementAndTexture(selected);
	sdlHandler->deleteRenderingElementAndTexture(unselected);
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
