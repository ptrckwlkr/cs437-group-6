#include "graphics/graphics_victory.h"
#include "views/player_view_menu.h"
#include "macros.h"

VictoryGraphics::VictoryGraphics(VictoryView *view) : Graphics(), view(view)
{
    // get all necessary resources from resource manager
    font = resources.GetFont("old_school");
    std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("text");
    buffer = resources.GetXMLBuffer("text");
    root_node = (*doc).first_node("Root")->first_node("Victory");
    storeStaticText();
}

void VictoryGraphics::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

    // This must always be the first line of every draw method
    states.transform *= getTransform();

//    if (view->screenIndex == 0)		//draw elements for title screen
//    {
//        drawTitleScreenDynamicText(target, states, view->selectionIndex);
//        target.draw(title, states);
//    }

}


/*
	Helper method to prepare all text items that will not be changed in any way
*/
void VictoryGraphics::storeStaticText()
{
    //title text
    title = prepareText("victory", font);
    //centers text
    title.setOrigin(title.getLocalBounds().width / 2.0, title.getLocalBounds().height / 2.0);
    title.setPosition(WINDOW_WIDTH / 2.0, 125);

}


/*
	helper function for drawDynamicText that draws text for the titleScreen
*/
void VictoryGraphics::drawTitleScreenDynamicText(sf::RenderTarget &target, sf::RenderStates states, int index) const
{
    sf::Text victoryText = prepareText("victory", font);

    //'s color is updated properly
    victoryText.setPosition(WINDOW_WIDTH / 2.0, 300);
    if (index == 0)
        victoryText.setFillColor(sf::Color::Cyan);
    else
        victoryText.setFillColor(sf::Color::White);

    target.draw(victoryText, states);

}