#ifndef CSCI437_GRAPHICS_NEXT_LEVEL_H
#define CSCI437_GRAPHICS_NEXT_LEVEL_H


#include "graphics.h"

class NextLevelView;
class NextLevelGraphics : public Graphics
{

public:
    explicit NextLevelGraphics(NextLevelView *view);

private:
    NextLevelView *view;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Font font;
    sf::Text title;
};

#endif //CSCI437_GRAPHICS_NEXT_LEVEL_H
