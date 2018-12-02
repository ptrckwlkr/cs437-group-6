#ifndef CSCI437_LEVEL_FACTORY_H
#define CSCI437_LEVEL_FACTORY_H

#include <fstream>
#include <string>
#include <memory>
#include "level.h"
#include "map.h"
#include "alg_agent_based.h"

enum Generator
{
	LEVEL_FILE,
	AGENT_BASED
};

class LevelFactory
{

public:
    LevelFactory() = default;
    void set_algorithm(Generator algorithm, int level);
    std::shared_ptr<Level> generate_level();

private:
    std::shared_ptr<Map> load(std::string filename);
    Generator algorithm;
    AgentBasedGenerator gen;
    int level_num;

};

#endif //CSCI437_LEVEL_FACTORY_H
