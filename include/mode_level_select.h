#ifndef CSCI437_MODE_LEVELSELECT_H
#define CSCI437_MODE_LEVELSELECT_H

#include "mode.h"
#include "level.h"

class LevelSelectMode : public Mode
{

public:
	LevelSelectMode();
	~LevelSelectMode() = default;
	void update() override;
	Level getSelectedLevel();

private:
	int selectionIndex;

};

#endif //CSI437_MODE_LEVELSELECT_H
