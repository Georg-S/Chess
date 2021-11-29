#pragma once
#include <iostream>
#include <SDL.h>
#include "MouseInformation.h"

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
