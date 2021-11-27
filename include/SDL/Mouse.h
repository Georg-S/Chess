#pragma once
#include <iostream>
#include "MouseInformation.h"
#include <SDL.h>

class Mouse
{
public:
	Mouse();
	void update();
	bool isLeftPressed();
	bool isRightPressed();
	bool isNewLeftClick();
	void getMousePosition(int& x, int& y);
	int getMousePositionX();
	int getMousePositionY();

private:
	bool lastTickLeftClicked = false;
	bool newLeftClick = false;
	MouseInformation mouseInfo{};
};
