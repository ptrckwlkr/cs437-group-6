#ifndef CSCI437_PLAYER_H
#define CSCI437_PLAYER_H

#include <memory>
#include "entities/entity.h"
#include "player_data.h"

#define PLAYER_SIZE  15

class Player: public Entity
{

private:
		PlayerData *data;
    float max_health = 1;
    float mana = 1;
    float max_mana = 1;
    float mana_regen = 0;
		float l_cooldown = 0;
		float r_cooldown = 0;
		float l_delta = 0;
		float r_delta = 0;

public:
		Player(float x, float y);
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}

    void update(float delta);
		void set_player_data(PlayerData *d);

    const float get_max_health() const {return max_health;}
    const float get_mana() const {return mana;}
    const float get_max_mana() const {return max_mana;}
    const float get_mana_regen() const {return mana_regen;}

    void l_attack(Vector2D &dir, float delta);
    void r_attack(Vector2D &dir, float delta);
    void die() override;

};

#endif //CSCI437_PLAYER_H