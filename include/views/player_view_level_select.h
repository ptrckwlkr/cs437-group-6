#ifndef CSCI437_VIEW_LEVELSELECT_H
#define CSCI437_VIEW_LEVELSELECT_H

#include "macros.h"
#include "player_view.h"

class LevelSelectView : public PlayerView
{

private:
    void process_input(float delta) override;
    void handle_event(sf::Event event) override;
    struct Node {
        int x;
        int y;
        int size;
    };
    Node nodes[NUMBER_OF_LEVELS];
    int clicked_node(int mouseX, int mouseY);
    int selected_level;

public:
    LevelSelectView(GameLogic *state, sf::RenderWindow *App);
    void update(float delta) override;
    void draw(float delta) override;
    Node get_node(int node) {return nodes[node];}

};


#endif //CSCI437_VIEW_LEVELSELECT_H
