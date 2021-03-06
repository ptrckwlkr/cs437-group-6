#ifndef CSCI437_SKELETON_H
#define CSCI437_SKELETON_H


#include "events/event_collision.h"
#include "events/event_entity_damaged.h"
#include "entity.h"
#include "enemy.h"

#define SKELETON_SIZE  15



class Skeleton : public Enemy
{

public:
    Skeleton(float x, float y);
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void givePathNodes(std::vector<Vector2D> &path) {path_nodes = path;}
    void die();

    std::vector<Vector2D> path_nodes;

private:
    void handleCollision(const EventCollision &event);

};


#endif //CSCI437_SKELETON_H
