#pragma once
#include <string>
#include "SDLHandler.h"

class SDLButton
{
public:
	SDLButton(SDLHandler* sdlHandler, int x, int y, int width, int height, std::string unselectedFilePath, std::string selectedFilePath);
	void updateButton(const int &mousePositionX,const int &mousePositionY,const bool &clicked);
	bool wasClicked();
	void destroy();
private: 
	bool isMouseOverButton(const int &mousePositionX, const int &mousePositionY);

	SDLHandler* sdlHandler;
	std::shared_ptr<RenderingElement> unselected;
	std::shared_ptr<RenderingElement>selected;
	bool clicked = false;

	int x;
	int y;
	int width;
	int height;
	std::string unselectedFilePath;
	std::string selectedFilePath;
};

