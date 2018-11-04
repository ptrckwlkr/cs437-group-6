#include <mode_menu.h>
#include "view_menu.h"
#include "macros.h"


MenuView::MenuView(GameLogic *state) : View(state)
{
	// get font from resource manager
	font = resources.GetFont("old_school");
}

void MenuView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

}


