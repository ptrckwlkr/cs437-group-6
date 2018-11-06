#include <mode_menu.h>
#include "view_menu.h"
#include "macros.h"


MenuView::MenuView(GameLogic *state) : View(state)
{
	// get all necessary resources from resource manager
	font = resources.GetFont("old_school");
	std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("text");
	buffer = resources.GetXMLBuffer("text");
	root_node = (*doc).first_node("Menu");
}

void MenuView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

}


