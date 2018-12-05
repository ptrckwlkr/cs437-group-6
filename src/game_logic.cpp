#include "game_logic.h"
#include "engine.h"
#include "view_manager.h"
#include "sprite_manager.h"
#include "EntityManager.h"
#include "events/event_cycle_complete.h"

GameLogic::GameLogic() : Listener() {
    level_factory = LevelFactory();
    player_data = PlayerData();
    collision_engine = CollisionEngine();
    f_paused = false;

    EventManager::Instance().registerListener(EventExitReached::eventType, this, &GameLogic::handleExitReached);
    EventManager::Instance().registerListener(EventPlayerDied::eventType, this, &GameLogic::handlePlayerDeath);
    EventManager::Instance().registerListener(EventVictory::eventType, this, &GameLogic::handleVictory);
}

GameLogic::~GameLogic() {
    EventManager::Instance().unregisterAll(this);
}

/**
 * Update the game state
 */
void GameLogic::update_state(float delta) {
    EventManager::Instance().processEvents(); // Pre-collision event processing
    EventCycleComplete e(delta);
    EventManager::Instance().sendEvent(e);
    if (!check_flags()) {
        EntityManager::Instance().getPlayer()->update(delta);
        collision_engine.hash_entities(level->get_map(), EntityManager::Instance().getEntites());
        level->update();
        collision_engine.check_collisions(level->get_map());
    }
    EventManager::Instance().processEvents(); // Post-collision event processing
}

/**
 * Start a new level.
 */
void GameLogic::create_new_level(Generator g, int level_num) {
    level_factory.set_algorithm(g, level_num);
    level = level_factory.generate_level();
    current_level = level_num;
    level->get_player().set_player_data(&player_data);
}

void GameLogic::reset() {
    collision_engine.reset();
    SpriteManager::Instance().reset();
    ViewManager::Instance().reset();
    EntityManager::Instance().reset();
    EventManager::Instance().reset();
}

bool GameLogic::check_flags() {
    if (f_floor_complete) {
        f_floor_complete = false;
        reset();
        create_new_level(AGENT_BASED, current_level);
        Engine::Instance().switch_mode(MODE_PLAY);
        return true;
    } else if (f_defeat) {
        f_defeat = false;
        reset();
        Engine::Instance().switch_mode(MODE_LOST);
        level_factory.reset();
        return true;
    } else if (f_victory) {
        f_victory = false;
        reset();
        Engine::Instance().switch_mode(MODE_VICTORY);
        level_factory.reset();
        return true;
    }
    return false;
}

void GameLogic::handleExitReached(const EventExitReached &event) {
    f_floor_complete = true;
}


void GameLogic::handlePlayerDeath(const EventPlayerDied &event)
{
    f_defeat = true;
}

void GameLogic::handleVictory(const EventVictory &event)
{
    f_victory = true;
}
