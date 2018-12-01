#ifndef CSCI437_GRAPHICS_MENU_H
#define CSCI437_GRAPHICS_MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "graphics.h"
#include "views/player_view.h"

class MenuView;
class MenuGraphics : public Graphics
{

public:
    explicit MenuGraphics(MenuView *view);

private:
    MenuView *view;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void storeStaticText();
    void storeControlText();
    void drawTitleScreenDynamicText(sf::RenderTarget &target, sf::RenderStates states, int index) const;

    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuInstructions;
    std::vector<sf::Text> controls;
    sf::Text aboutText;

};


#endif //CSCI437_GRAPHICS_MENU_H