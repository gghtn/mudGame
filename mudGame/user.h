#pragma once
#include "object.h"
#include "monster.h"
#pragma warning(disable:4996)

class CUser :public CObject{
	bool mb_normalAtk, mb_skillAtk;
	int mWeaponATK, mPoint, mExp, mTotalExp, mGold;
	unsigned char skill;
public:
	CUser(string);

	string Attack(CObject* pObject);

	//void SkillAttack(CObject* pObject);

	int GetExp() { return mExp; }
	int GetTotalExp() { return mTotalExp; }
	int GetGold() { return mGold; }
};