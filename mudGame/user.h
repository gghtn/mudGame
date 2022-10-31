#pragma once
#include "object.h"
#include "monster.h"
#pragma warning(disable:4996)

class CUser :public CObject {
	//무기 공격력, 정확도, 회복력, 포인트, 경험치, 총 경험치, 골드, 아이템
	int mWeaponClass, mWeaponATK, mAccuracy, mResilience, mPoint, mExp, mTotalExp, mGold, mItem;
	bool skill[4];
	static int killCount;
public:
	CUser(string);

	string Attack(CObject* pMonster);			//기본 공격

	string SkillActivate(CObject* pMonster);	//스킬 활성화

	bool AttackFail(CObject* pMonster);			//공격 성공 여부

	//스킬 사용
	string TripleAttack(CObject* pMonster, int mp);
	string Recovery(int mp);
	string TrueAttack(CObject* pMonster, int mp);
	string AuraBlade(CObject* pMonster, int mp);

	char* Loot(CObject* pMonster); //전리품-경험치, 골드, 아이템

	//get
	int GetWeaponClass() { return mWeaponClass; }
	int GetWeapon() { return mWeaponATK; }
	int GetAccuracy() { return mAccuracy; }
	int GetResilience() { return mResilience; }
	int GetPoint() { return mPoint; }
	int GetExp() { return mExp; }
	int GetTotalExp() { return mTotalExp; }
	int GetGold() { return mGold; }
	int GetItem() { return mItem; }
	int GetKillCount() { return killCount; }
	bool GetSkill(int i) { return skill[i]; }

	//set
	void SetKillCountZero() { killCount = 0; }
	void InhanceWeapon() { mWeaponATK += 50; }
	void WeaponUP() { mWeaponClass++; }
	void SetAccuracy() { mAccuracy++; }
	void SetResilience() { mResilience += 10; }
	void SetPoint() { mPoint--; }
	void SetItemGold(int num) { mItem -= num, mGold -= num * 100; }

	void LevelUp();			//레벨업
	void AutoRecovery();	//자동회복
	void LoseExp();			//경험치 손실- 죽었을 경우, 중간 퇴장
};