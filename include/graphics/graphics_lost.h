#ifndef CSCI437_GRAPHICS_LOST_H
#define CSCI437_GRAPHICS_LOST_H

#include "graphics.h"
#include "views/player_view_lost.h"
#include <string>

class LostView;
class LostGraphics : public Graphics
{

public:
    explicit LostGraphics(LostView *view);

private:
    LostView *view;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuInstructions;
    std::vector<sf::Text> controls;
    sf::Text aboutText;

};


#endif //CSCI437_GRAPHICS_LOST_H
