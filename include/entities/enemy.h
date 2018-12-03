//
// Created by Ian on 12/2/2018.
//

#ifndef CSCI437_ENEMY_H
#define CSCI437_ENEMY_H

#include "events/event.h"
#include "entities/entity.h"

class Enemy: public Entity
{

public:
    Enemy(float x, float y, float size) : Entity(x, y, size) {
        std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("enemies");
        buffer = resources.GetXMLBuffer("enemies");
        root_node = (*doc).first_node("Root");
    };




};

#endif //CSCI437_ENEMY_H

