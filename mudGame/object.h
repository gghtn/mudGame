#pragma once
#include <iostream>
#include <string>
using namespace std;

class CObject {
	string mName;
	bool mbLive;
	int mLevel, mHP, mMP, mMaxHP, mMaxMP, mSTR, mDEX, mDEF;
public:
	CObject();
	virtual ~CObject() {}

	virtual string Attack(CObject* pObject) = 0;	// 기본 공격 함수
	float LevelWeight(CObject* pMonster);			// 레벨 가중치

	void SetInitAll(string);

	const char* GetName() { return mName.c_str(); }
	bool GetLive() { return mbLive; }
	int GetLevel() { return mLevel; }
	int GetHP() { return mHP; }
	int GetMP() { return mMP; }
	int GetMaxHP() { return mMaxHP; }
	int GetMaxMP() { return mMaxMP; }
	int GetSTR() { return mSTR; }
	int GetDEX() { return mDEX; }
	int GetDEF() { return mDEF; }

	void SetDamage(int damage);
	void SetName(string name) { mName = name; }
	void SetLive() { mbLive = !mbLive; }
	void SetLevel(int num) { mLevel = num; }
	void SetHP(int num) { mHP = num; }
	void SetMP(int num) { mMP = num; }
	void SetMaxHP(int num) { mMaxHP = num; }
	void SetMaxMP(int num) { mMaxMP = num; }
	void SetSTR(int num) { mSTR = num; }
	void SetDEX(int num) { mDEX = num; }
	void SetDEF(int num) { mDEF = num; }

	void UseMP(int num) { mMP -= num; }
};