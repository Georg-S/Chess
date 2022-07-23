#pragma once
#include <string>
#include "SDLHandler.h"

class SDLButton
{
public:
	SDLButton(SDLHandler* sdlHandler, int x, int y, int width, int height, std::string unselectedFilePath, std::string selectedFilePath);
	void updateButton(const int &mousePositionX,const int &mousePositionY,const bool &clicked);
	bool wasClicked();
private: 
	bool isMouseOverButton(const int &mousePositionX, const int &mousePositionY);

	SDLHandler* sdlHandler;
	const RenderingElement* unselected = nullptr;
	const RenderingElement* selected = nullptr;
	bool clicked = false;

	int x;
	int y;
	int width;
	int height;
	std::string unselectedFilePath;
	std::string selectedFilePath;
};

