#pragma once

#include "dungeon.h"
#include "orc.h"
#include "orc_king.h"

class COrcDungeon : public CDungeon {
public:
	COrcDungeon(CObject* p) :CDungeon(p) {
		SetDungeonName("오크 서식지");
		SetMonsterCount(NUM_ORC);
	}
	void DungeonStart();
};