#include "mode_menu.h"

MenuMode::MenuMode()
{
	selectionIndex = 0;
	screenIndex = 0;
}

void MenuMode::update()
{

}

/*
	Triggered by menu controller, determines which menu option the player has selected
	and performs the appropriate action. 
	returns true if mode is to be changed false otherwise
*/
bool MenuMode::makeSelection()
{
	if (screenIndex == 0) //title screen
	{
		if (selectionIndex == 0) //play game has been selected
			return true;
		else if (selectionIndex == 1) //controls have been selected
			screenIndex = 1;
		else							//about game has been selected
			screenIndex = 2;
	}

	return false;
}

/*
	called by Menu Controller, allows player to go back to an earlier menu screen
*/
void MenuMode::goBack()
{
	if (screenIndex != 0)
		screenIndex = 0;

}