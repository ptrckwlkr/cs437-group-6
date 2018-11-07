#ifndef CSCI437_MODE_MENU_H
#define CSCI437_MODE_MENU_H

#include "mode.h"

class MenuMode : public Mode
{

public:
	MenuMode();
	~MenuMode() = default;
	void update() override;

	int selectionIndex;	//represents current highlighted option on screen
	int screenIndex;	//represents current menu screen to display

private:

};

#endif //CSI437_MODE_MENU_H