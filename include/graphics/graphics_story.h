#ifndef CSCI437_GRAPHICS_STORY_H
#define CSCI437_GRAPHICS_STORY_H


#include "graphics.h"
#include "graphics.h"

class StoryView;
class StoryGraphics : public Graphics
{

public:
    explicit StoryGraphics(StoryView *view);

private:
    StoryView *view;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuInstructions;
    std::vector<sf::Text> controls;
    sf::Text aboutText;

};

#endif //CSCI437_GRAPHICS_STORY_H
