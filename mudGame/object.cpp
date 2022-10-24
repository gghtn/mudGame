#include "object.h"

CObject::CObject() {
	mName = "";
	mbLive = true;
	mLevel = 1, mHP = 0, mMP = 0, mSTR = 0, mDEX = 0, mDEF = 0;
}

void CObject::SetInitAll(string name) {
	mName = name;
	mbLive = true;
	mLevel = 1, mHP = 100, mMP = 100, mSTR = 10, mDEX = 10, mDEF = 10;
}

void CObject::SetDamage(int damage) {
	mHP -= damage;
	if (mHP <= 0) {
		mHP = 0;
		mbLive = false;
	}
}