#pragma once

#include "dungeon.h"
#include "goblin.h"
#include "goblin_king.h"

class CGoblinDungeon : public  CDungeon {
public:
	CGoblinDungeon(CObject* p) :CDungeon(p) {
		SetDungeonName("°íºí¸° ½£");
		SetMonsterCount(NUM_GOBLIN);
	}
	void DungeonStart();
};