#include "scarecrow_dungeon.h"

void CScarecrowDungeon::DungeonStart() {

	ScreenInit();
	int count = GetMonsterCount();
	CObject** p = new CObject * [count];	//몬스터 생성 이중포인터
	if (p == NULL) return;
	for (int i = 0; i < count; i++) {
		p[i] = new CScarecrow;
	}
	Battle(p);
	delete[] p;
	ScreenRelease();
}