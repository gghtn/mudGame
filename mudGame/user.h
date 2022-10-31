#pragma once
#include "object.h"
#include "monster.h"
#pragma warning(disable:4996)

class CUser :public CObject {
	//���� ���ݷ�, ��Ȯ��, ȸ����, ����Ʈ, ����ġ, �� ����ġ, ���, ������
	int mWeaponClass, mWeaponATK, mAccuracy, mResilience, mPoint, mExp, mTotalExp, mGold, mItem;
	bool skill[4];
	static int killCount;
public:
	CUser(string);

	string Attack(CObject* pMonster);			//�⺻ ����

	string SkillActivate(CObject* pMonster);	//��ų Ȱ��ȭ

	bool AttackFail(CObject* pMonster);			//���� ���� ����

	//��ų ���
	string TripleAttack(CObject* pMonster, int mp);
	string Recovery(int mp);
	string TrueAttack(CObject* pMonster, int mp);
	string AuraBlade(CObject* pMonster, int mp);

	char* Loot(CObject* pMonster); //����ǰ-����ġ, ���, ������

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

	void LevelUp();			//������
	void AutoRecovery();	//�ڵ�ȸ��
	void LoseExp();			//����ġ �ս�- �׾��� ���, �߰� ����
};