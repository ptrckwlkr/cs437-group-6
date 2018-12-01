#ifndef CSCI437_GRAPHICS_INVENTORY_H
#define CSCI437_GRAPHICS_INVENTORY_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "graphics.h"
#include "views/player_view.h"

class InventoryView;
class InventoryGraphics : public Graphics
{

public:
    explicit InventoryGraphics(InventoryView *view);

private:
		InventoryView *view;

	  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	  std::vector<sf::Drawable> menuObjects;
	  sf::Font font;
};


#endif //CSCI437_GRAPHICS_INVENTORY_H
