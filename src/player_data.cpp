#include "macros.h"
#include "player_data.h"
#include "EntityManager.h"
#include "entities/Player.h"

PlayerData::PlayerData()
{
  base_speed = PLAYER_SPEED;
  base_health = 100;
  base_max_health = 100;
  base_mana = 100;
  base_defence = 10;
  base_damage = 5;
  gold = STARTING_GOLD;
  health = base_health;
  mana = base_mana;
}

void PlayerData::handleCollision(const EventGoldCollection &event)
{
    gold +=10;
}

void PlayerData::set_player(Player *p)
{
  player = p;
  set_health();
  set_mana();
  set_speed();
  set_damage();
  set_defence();
  set_max_health();
  set_max_mana();
  set_mana_regen();
}

void PlayerData::reset()
{
  health = base_health;
  mana = base_mana;
  gold = gold;
  set_health();
  set_mana();
}

void PlayerData::update()
{
  health = player->get_health();
  mana = player->get_mana();
}

void PlayerData::set_health()
{
  player->set_health(health);
}

void PlayerData::set_mana()
{
  player->set_mana(mana);
}

void PlayerData::set_speed()
{
  player->set_speed(base_speed);
}

void PlayerData::set_damage()
{
  player->set_damage(base_damage);
}

void PlayerData::set_defence()
{
  player->set_defence(base_defence);
}

void PlayerData::set_max_health()
{
  player->set_max_health(base_max_health);
}

void PlayerData::set_max_mana()
{
  player->set_max_mana(base_max_mana);
}

void PlayerData::set_mana_regen()
{
  player->set_mana_regen(base_mana_regen);
}

void PlayerData::update_gold( bool defeat) {
  if (defeat) gold = STARTING_GOLD;
  else gold +=10;
}