#include "graphics/graphics_next_level.h"

NextLevelGraphics::NextLevelGraphics(NextLevelView *view) : Graphics(), view(view)
{
    // get all necessary resources from resource manager
    font = resources.GetFont("old_school");
    std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("text");
    buffer = resources.GetXMLBuffer("text");
    root_node = (*doc).first_node("Root")->first_node("NextLevel");
}

void NextLevelGraphics::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    // This must always be the first line of every draw method
    states.transform *= getTransform();
    camera_reset(target);
    sf::Text title = prepareText("NextLevelText", font);
    sf::Text stats;
    sf::Text playAgain = prepareText("Cont", font);
    //centers text
    title.setOrigin(title.getLocalBounds().width / 2.0, title.getLocalBounds().height / 2.0);
    title.setPosition(WINDOW_WIDTH / 2, 250);
    playAgain.setOrigin(title.getLocalBounds().width / 8.0, title.getLocalBounds().height / 8.0);
    playAgain.setPosition(WINDOW_WIDTH / 2.3, 400);

    target.draw(title, states);
    target.draw(playAgain, states);
}