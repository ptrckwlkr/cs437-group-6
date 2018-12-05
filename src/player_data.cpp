#include "EventManager.h"
#include "macros.h"
#include "player_data.h"

PlayerData::PlayerData() : Listener()
{
  gear            = GearSet();
  base_damage     = 5;
  base_defence    = 5;
  base_speed      = PLAYER_SPEED;
  base_max_health = 100;
  base_max_mana   = 100;
  base_mana_regen = 1;
  gold            = STARTING_GOLD;
  level_gold      = 0;

  EventManager::Instance().registerListener(EventGoldCollection::eventType, this, &PlayerData::handleGoldCollection);
  EventManager::Instance().registerListener(EventPlayerDied::eventType, this, &PlayerData::handlePlayerDeath);
  //EventManager::Instance().registerListener(EventPlayerDied::eventType, this, &handleLevelComplete);
}

PlayerData::~PlayerData()
{
  EventManager::Instance().unregisterAll(this);
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

void PlayerData::handleGoldCollection(const EventGoldCollection &event)
{
  level_gold += 10;
}

void PlayerData::handlePlayerDeath(const EventPlayerDied &event)
{
  level_gold = 0;
}

void PlayerData::handleLevelComplete(const EventPlayerDied &event)
{
  gold += level_gold;
  level_gold = 0;
}
