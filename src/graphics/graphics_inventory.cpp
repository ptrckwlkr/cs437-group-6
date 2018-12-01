#include "graphics/graphics_inventory.h"
#include "views/player_view_inventory.h"

InventoryGraphics::InventoryGraphics(InventoryView *view) : Graphics(), view(view)
{

}

void InventoryGraphics::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

	// This must always be the first line of every draw method
	states.transform *= getTransform();

}


