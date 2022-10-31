#include "scarecrow.h"

CScarecrow::CScarecrow() :CMonster() {
	SetName("수련용 허수아비");

	Init(GetName(), LEVEL_WEIGHT_SCARECROW);
}

void CScarecrow::Init(string name, int weight) {
	SetName(name);
	int num = rand() % weight + 1;
	SetLevel(num);
	SetMaxHP(num * 10);
	SetHP(GetMaxHP());
	SetSTR(num);
	SetDEX(num);
	SetDEF(num);
	SetMonsterInfo(EXP_SCARECROW, GOLD_SCARECROW, ITEM_SCARECROW);
}