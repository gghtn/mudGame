#include "scarecrow.h"

CScarecrow::CScarecrow() :CMonster() {
	mName = "���ÿ� ����ƺ�";

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