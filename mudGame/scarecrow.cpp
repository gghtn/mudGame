#include "scarecrow.h"

CScarecrow::CScarecrow() :CMonster() {
	mName = "수련용 허수아비";

	Init(mName, WEIGHT_SCARECROW);
}

void CScarecrow::Init(string name, int weight) {
	SetName(name);
	int num = rand() % weight + 1;
	SetLevel(num);
	SetHP(num * 10);
	SetSTR(num);
	SetDEX(num);
	SetDEF(num);
}