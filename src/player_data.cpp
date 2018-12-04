#include "macros.h"
#include "player_data.h"

PlayerData::PlayerData()
{
  gear            = GearSet();
  base_damage     = 5;
  base_defence    = 5;
  base_speed      = PLAYER_SPEED;
  base_max_health = 100;
  base_max_mana   = 100;
  base_mana_regen = 1;
  gold            = STARTING_GOLD;
}

void PlayerData::handleCollision(const EventGoldCollection &event)
{
    gold += 10;
}

void PlayerData::reset()
{
  health = get_max_health();
  mana = get_max_mana();
}

float PlayerData::get_health()
{
   return health;
}

float PlayerData::get_mana()
{
  return mana;
}

float PlayerData::get_speed()
{
  return base_speed;
}

float PlayerData::get_damage()
{
  return base_damage + gear.getSetStat("Attack");
}

float PlayerData::get_defence()
{
  return base_defence + gear.getSetStat("Defense");
}

float PlayerData::get_max_health()
{
  return base_max_health + gear.getSetStat("Health");
}

float PlayerData::get_max_mana()
{
  return base_max_mana + gear.getSetStat("Mana");
}

float PlayerData::get_mana_regen()
{
  return base_mana_regen + gear.getSetStat("Magic");
}

float PlayerData::get_l_cooldown()
{
  return (float)(45 / 60.0); //TODO
}

float PlayerData::get_r_cooldown()
{
  return (float)(52 / 60.0); //TODO
}

float PlayerData::get_l_mana_cost()
{
  return 5; //TODO
}

void PlayerData::update_gold(bool defeat) {
  if (defeat) gold = STARTING_GOLD;
  else gold += 10;
}
