#include "level_factory.h"
#include "views/view_skeleton.h"
#include "view_manager.h"
#include "entities/gold.h"
#include "entities/exit.h"
#include "EntityManager.h"
#include "level.h"
#include <unordered_map>
#include "entities/ghost.h"
#include "entities/orc.h"



void LevelFactory::set_algorithm(Generator algorithm, int level)
{
    this->algorithm = algorithm;

    if (level_num != level || reset_occurred)
    {
        gen = AgentBasedGenerator(level);
        reset_occurred = false;
    }

    level_num = level;
}



/**
 * Returns a pointer to a newly created level, which is built according to the parameters specified through the setter
 * methods
 */
std::shared_ptr<Level> LevelFactory::generate_level() {
    std::shared_ptr<Level> level;
    std::shared_ptr<Map> map;


    // TODO Can specify the map generation algorithm (load from file, randomly generated, etc)
    switch (algorithm) {
        case LEVEL_FILE:

            EntityManager::Instance().getPlayer()->set_position(150, 150);

            map = load("../data/test2.txt");
            break;
        case AGENT_BASED:

            gen.createLevelGrid();
            map = std::make_shared<Map>(gen.level_grid);
            map->givePathNodes(gen.getPathNodes());
            //gen.printLevelGrid();

            std::shared_ptr<Player> player = EntityManager::Instance().createEntity<Player>(gen.player_x,
                                                                                             gen.player_y);
        EntityManager::Instance().setPlayer(player);

            placeEnemies();


            for (int i = 0; i < gen.treasure_coords.size(); i++) {
                auto ent = EntityManager::Instance().createEntity<Gold>((float) gen.treasure_coords[i][0],
                                                                         (float) gen.treasure_coords[i][1]);
            }
            EntityManager::Instance().createEntity<Exit>(gen.exit_x + CELL_SIZE / 2, gen.exit_y + CELL_SIZE / 2);
            break;
    }

    // Create the actual level
    level = std::make_shared<Level>(map);
    level->set_player(EntityManager::Instance().getPlayer().get());

    return level;
}

std::shared_ptr<Map> LevelFactory::load(std::string filename) {
    std::ifstream fin;
    std::string linestr;
    std::vector<std::vector<char>> grid;
    std::vector<char> temp;
    fin.open(filename, std::ios::in);

    while (std::getline(fin, linestr)) {
        for (auto c : linestr) {
            temp.push_back(c);
        }
        grid.push_back(temp);
        temp.clear();
    }

    fin.close();
    return std::make_shared<Map>(grid);
}


void LevelFactory::placeEnemies()
{
    //places all enemies using an unordered map made by the call to createLevelGrid()
    for (const auto it : gen.enemy_type_coords) {
        for (const auto v : it.second) {
            if (it.first == "skeleton-white" || it.first == "skeleton-red" || it.first == "skeleton-gold")
            {
                auto ent = EntityManager::Instance().createEntity<Skeleton>((float) v[0], (float) v[1]);
                ent->setType(it.first);
            }
            else if (it.first == "ghost-white" || it.first == "ghost-red" || it.first == "ghost-gold")
            {
                auto ent = EntityManager::Instance().createEntity<Ghost>((float) v[0], (float) v[1]);
                ent->setType(it.first);
            }
            else if (it.first == "orc-green" || it.first == "orc-red" || it.first == "orc-gold")
            {
                auto ent = EntityManager::Instance().createEntity<Orc>((float) v[0], (float) v[1]);
                ent->setType(it.first);
            }
        }
    }

}