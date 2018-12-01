#ifndef CSCI437_GRAPHICS_VICTORY_H
#define CSCI437_GRAPHICS_VICTORY_H

#include <vector>
#include <string>
#include "graphics.h"
#include "views/player_view.h"

class VictoryView;
class VictoryGraphics : public Graphics
{

public:
    explicit VictoryGraphics(VictoryView *view);

private:
    VictoryView *view;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuInstructions;
    std::vector<sf::Text> controls;
    sf::Text aboutText;

};


#endif //CSCI437_GRAPHICS_VICTORY_H
