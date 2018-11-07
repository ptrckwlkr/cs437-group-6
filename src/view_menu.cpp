#include <mode_menu.h>
#include "view_menu.h"
#include "macros.h"
#include <iostream>

MenuView::MenuView(GameLogic *state) : View(state)
{
	// get all necessary resources from resource manager
	font = resources.GetFont("old_school");
	std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("text");
	buffer = resources.GetXMLBuffer("text");

	root_node = (*doc).first_node("Root")->first_node("Menu");

	storeStaticText();
}

void MenuView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// This must always be the first line of every draw method
	states.transform *= getTransform();
	
	target.draw(title, states);
	drawDynamicText(target, states);


}


/*
	Helper method to prepare all text items that will not be changed in any way 
*/
void MenuView::storeStaticText()
{
	title = prepareText("title");
	title.setFont(font);
	//centers text
	title.setOrigin(title.getLocalBounds().width / 2.0, title.getLocalBounds().height / 2.0);
	title.setPosition(WINDOW_WIDTH / 2.0, 125);

	//prepares for when the dynamic buttons are created
	root_node = root_node->first_node("buttons");

}

/*
	draws dynamic text  (text that changes colors) for the current menu screen
*/
void MenuView::drawDynamicText(sf::RenderTarget &target, sf::RenderStates states) const
{
	//if the mode's selection index and views are not equal, make necessary changes
	auto mode = std::dynamic_pointer_cast<MenuMode>(state->get_mode());

	if (mode->screenIndex == 0) //title screen
		drawTitleScreenDynamicText(target, states, mode->selectionIndex);
	
}

/*
	helper function for drawDynamicText that draws text for the titleScreen
*/
void MenuView::drawTitleScreenDynamicText(sf::RenderTarget &target, sf::RenderStates states, int index) const
{

	sf::Text playButton = prepareText("title-first");
	sf::Text controlsButton = prepareText("title-second");
	sf::Text exitButton = prepareText("title-third");

	//play button is updated properly
	playButton.setFont(font);
	playButton.setOrigin(playButton.getLocalBounds().width / 2.0, playButton.getLocalBounds().height / 2.0);
	playButton.setPosition(WINDOW_WIDTH / 2.0, 350);
	if (index == 0)
		playButton.setFillColor(sf::Color::Cyan);
	else
		playButton.setFillColor(sf::Color::White);

	//controls button is updated properly
	controlsButton.setFont(font);
	controlsButton.setOrigin(controlsButton.getLocalBounds().width / 2.0, controlsButton.getLocalBounds().height / 2.0);
	controlsButton.setPosition(WINDOW_WIDTH / 2.0, 400);
	if (index == 1)
		controlsButton.setFillColor(sf::Color::Cyan);
	else
		controlsButton.setFillColor(sf::Color::White);
	
	//exit button is updated properly
	exitButton.setFont(font);
	exitButton.setOrigin(exitButton.getLocalBounds().width / 2.0, exitButton.getLocalBounds().height / 2.0);
	exitButton.setPosition(WINDOW_WIDTH / 2.0, 450);
	if (index == 2)
		exitButton.setFillColor(sf::Color::Cyan);
	else
		exitButton.setFillColor(sf::Color::White);

	target.draw(playButton, states);
	target.draw(controlsButton, states);
	target.draw(exitButton, states);
}