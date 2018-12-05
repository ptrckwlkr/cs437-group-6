#include "graphics/graphics_level_select.h"
#include "views/player_view_level_select.h"

LevelSelectGraphics::LevelSelectGraphics(LevelSelectView *view) : Graphics(), view(view)
{
    font = resources.GetFont("old_school");
    std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("text");
    buffer = resources.GetXMLBuffer("text");
    root_node = (*doc).first_node("Root")->first_node("LevelSelect");
}

void LevelSelectGraphics::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

    // This must always be the first line of every draw method
    states.transform *= getTransform();
    camera_reset(target);

    sf::Sprite sprite;
    sprite.setTexture(resources.GetTexture("map"));
    target.draw(sprite, states);

    sf::Text instructions = prepareText("LevelText", font);
    instructions.setPosition(WINDOW_WIDTH/ 2.0, sprite.getGlobalBounds().height + 30 );
    target.draw(instructions, states);


    for (int i = 0; i < NUMBER_OF_LEVELS; ++i) {
        sf::Sprite marker;
        marker.setTexture(resources.GetTexture("marker"));
        marker.setScale(0.75, 0.75);
        marker.setOrigin(marker.getTexture()->getSize().x / 2, marker.getTexture()->getSize().y / 2);
        marker.setPosition(view->get_node(i).x, view->get_node(i).y);
		    target.draw(marker, states);

        sf::Text level_num;
        level_num.setFont(resources.GetFont("old_school"));
        level_num.setString(std::to_string(i + 1));
        level_num.setCharacterSize(16);
        level_num.setFillColor(sf::Color::White);
        level_num.setOrigin(level_num.getLocalBounds().width / 2, level_num.getLocalBounds().height / 2);
        level_num.setPosition(view->get_node(i).x, view->get_node(i).y - 5);
        target.draw(level_num, states);
	  }
}


