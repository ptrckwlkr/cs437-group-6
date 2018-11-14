#ifndef CSCI437_ENEMY_H
#define CSCI437_ENEMY_H

#include "event.h"
#include "entity.h"

class Enemy: public Entity
{

public:
    Enemy(float x, float y, float size);
    ~Enemy();
    virtual void update(double deltaMs) = 0;
    void move(Vector2D &dir, float delta) override;
    void HandleEvent(Event* event) override;

}; 

#endif //CSCI437_ENEMY_H