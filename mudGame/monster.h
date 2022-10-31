#pragma once
#include "object.h"
#include "monster_info.h"
#pragma warning(disable:4996)

class CMonster : virtual public CObject {
	int mMonsterExp, mMonsterGold, mItemWeight;
public:
	CMonster() : CObject() { mMonsterExp = 0, mMonsterGold = 0, mItemWeight = 0; }
	virtual ~CMonster() {}

	//object 멤버변수 초기화
	void Init(string name, int weight, int status, int exp, int gold, int item);
	//몬스터 경험치, 골드, 아이템확률 정보set
	void SetMonsterInfo(int exp, int gold, int item) { mMonsterExp = exp, mMonsterGold = gold, mItemWeight = item; }

	int GetMonsterExp() { return mMonsterExp; }
	int GetMonsterGold() { return mMonsterGold; }
	int GetItemWeight() { return mItemWeight; }

	string Attack(CObject* pObject);
};