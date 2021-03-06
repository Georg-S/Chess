#pragma once
#include <string>
#include <memory>
#include "Chess/Constant.h"
#include "SDL/SDLHandler.h"
#include "SDL/SDLButton.h"
#include "SDL/Mouse.h"

class PlayerCountSelection
{
public:
	PlayerCountSelection(SDLHandler* sdlHandler);
	void createPlayerSelection();
	int getSelectedPlayerCount();
	void destroy();
	void update();

private:

	SDLHandler* sdlHandler;
	SDLButton* onePlayer = nullptr;
	SDLButton* twoPlayer = nullptr;
	Mouse mouse;

	const std::string headerPath = "Images/PlayerCountSelection/Header.png";
	const std::string onePlayerUnselectedPath = "Images/PlayerCountSelection/1Player_Unselected.png";
	const std::string onePlayerSelectedPath = "Images/PlayerCountSelection/1Player_Selected.png";
	const std::string twoPlayerSelectedPath = "Images/PlayerCountSelection/2Player_Selected.png";
	const std::string twoPlayerUnselectedPath = "Images/PlayerCountSelection/2Player_Unselected.png";
};
