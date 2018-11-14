#include "level.h"

Level::Level(std::shared_ptr<Map> &map) : map(std::move(map))
{

}

// std::vector<std::shared_ptr<Entity>> Level::get_entities(){
//     return EntityManager::Instance()->getEntites();
// }

// std::vector<Projectile*> Level::get_projectile(){
//     return EntityManager::Instance()->getProjectiles();
// }

void Level::update()
{

}
