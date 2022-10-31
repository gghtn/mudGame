#pragma once

#include "dungeon.h"
#include "scarecrow.h"

class CScarecrowDungeon : public CDungeon {
public:
	CScarecrowDungeon(CObject* p) : CDungeon(p) {
		SetDungeonName("���� ������");
		SetMonsterCount(NUM_SCARECROW);
	}
	void DungeonStart();
};