#ifndef CSCI437_VIEW_MENU_H
#define CSCI437_VIEW_MENU_H

#include <SFML/Graphics.hpp>
#include "game_logic.h"
#include "graphics.h"
#include "view_menu.h"
#include <vector>
#include <string>


class MenuGraphics : public Graphics
{

public:
    MenuGraphics(MenuView *view);
    MenuView *view;

private:
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


#endif //CSCI437_VIEW_MENU_H