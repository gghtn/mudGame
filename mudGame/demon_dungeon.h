#pragma once

#include "dungeon.h"
#include "demon.h"
#include "demon_king.h"

class CDemonDungeon : public  CDungeon {
public:
	CDemonDungeon(CObject* p) :CDungeon(p) {
		SetDungeonName("������ ��");
		SetMonsterCount(NUM_DEMON);
	}
	void DungeonStart();
};