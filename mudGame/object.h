#pragma once
#include <iostream>
#include <string>
using namespace std;

class CObject {
	string mName;
	bool mbLive;
	int mLevel, mHP, mMP, mSTR, mDEX, mDEF;
public:
	CObject();

	virtual string Attack(CObject* pObject) = 0;

	void SetInitAll(string);

	const char* GetName() { return mName.c_str(); }
	bool GetLive() { return mbLive; }
	int GetLevel() { return mLevel; }
	int GetHP() { return mHP; }
	int GetMP() { return mMP; }
	int GetSTR() { return mSTR; }
	int GetDEX() { return mDEX; }
	int GetDEF() { return mDEF; }

	void SetDamage(int damage);
	void SetName(string name) { mName = name; }
	void SetLevel(int num) { mLevel = num; }
	void SetHP(int num) { mHP = num; }
	void SetMP(int num) { mMP = num; }
	void SetSTR(int num) { mSTR = num; }
	void SetDEX(int num) { mDEX = num; }
	void SetDEF(int num) { mDEF = num; }
};