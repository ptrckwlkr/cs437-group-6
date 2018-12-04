#include "level.h"

Level::Level(std::shared_ptr<Map> &map) : map(std::move(map))
{

}

void Level::set_player(Player *p)
{
    player = p;
    player_prev_x = (int) player->get_position().x / CELL_SIZE;
    player_prev_y = (int) player->get_position().y / CELL_SIZE;
}



void Level::update()
{
    int new_x = (int) player->get_position().x / CELL_SIZE;
    int new_y = (int) player->get_position().y / CELL_SIZE;

    if (new_x != player_prev_x || new_y != player_prev_y)
        map->updatePlayerRecentCells(player->get_position());

    player_prev_x = new_x;
    player_prev_y = new_y;

    map->updateVisited(player->get_position());
}
