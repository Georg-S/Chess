#pragma once
#include <string>
#include <memory>
#include "SDL/SDLHandler.h"
#include "SDL/SDLButton.h"
#include "SDL/Mouse.h"

class PlayerCountSelection
{
public:
	PlayerCountSelection(SDLHandler* sdlHandler, int windowWidth, int windowHeight);
	void createPlayerSelection();
	int getSelectedPlayerCount();
	void destroy();
	void update();

private:

	SDLHandler* sdlHandler;
	std::shared_ptr<RenderingElement> header;
	SDLButton* onePlayer;
	SDLButton* twoPlayer;
	Mouse mouse;

	const std::string headerPath = "Images/PlayerCountSelection/Header.png";
	const std::string onePlayerUnselectedPath = "Images/PlayerCountSelection/1Player_Unselected.png";
	const std::string onePlayerSelectedPath = "Images/PlayerCountSelection/1Player_Selected.png";
	const std::string twoPlayerSelectedPath = "Images/PlayerCountSelection/2Player_Selected.png";
	const std::string twoPlayerUnselectedPath = "Images/PlayerCountSelection/2Player_Unselected.png";

	int windowWidth;
	int windowHeight;
};
