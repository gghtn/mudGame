#include "orc_dungeon.h"

void COrcDungeon::DungeonStart() {
	ScreenInit();
	int count = GetMonsterCount();
	CObject** p = new CObject * [count];
	if (p == NULL) return;
	for (int i = 0; i < count; i++) {
		if (i == count - 1) p[i] = new COrcKing;
		else p[i] = new COrc;
	}
	Battle(p);
	delete[] p;
	ScreenRelease();
}