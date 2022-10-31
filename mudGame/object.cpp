#include "object.h"

CObject::CObject() {
	mName = "";
	mbLive = true;
	mLevel = 1, mHP = 0, mMP = 0, mMaxHP = 0, mMaxMP = 0, mSTR = 0, mDEX = 0, mDEF = 0;
}

void CObject::SetInitAll(string name) {
	mName = name;
	mbLive = true;
	mLevel = 1, mHP = 100, mMP = 100, mMaxHP = 100, mMaxMP = 100, mSTR = 10, mDEX = 10, mDEF = 10;
}

void CObject::SetDamage(int damage) {
	mHP -= damage;
	if (mHP <= 0) {
		mHP = 0;
		mbLive = false;
	}
}

//레벨 가중치
float CObject::LevelWeight(CObject* pMonster) {
	float weight;
	weight = (float)GetLevel() - pMonster->GetLevel();
	if (weight < -20 && weight > -100) weight = 1.0f + (weight / 100);
	else if (weight < -100) weight = 0.0f;
	else if (weight > 20) weight = 1.0f + (weight / 100);
	else weight = 1.0f;
	return weight;
}