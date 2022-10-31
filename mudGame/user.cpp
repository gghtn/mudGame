#include "user.h"
#include "skill.h"
#include "key_pos.h"
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int CUser::killCount = 0;

CUser::CUser(string name) :CObject() {
	mWeaponClass = 1, mWeaponATK = 100, mAccuracy = 10, mResilience = 10, mPoint = 0, mExp = 0, mTotalExp = 100, mGold = 0, mItem = 0;
	for (int i = 0; i < 4; i++) {
		skill[i] = false;
	}
	SetInitAll(name);
}

//�Ϲ� ����
string CUser::Attack(CObject* pMonster) {
	char result[300];
	int damage;
	bool attack_failed;
	float weight;

	attack_failed = AttackFail(pMonster);

	if (attack_failed) damage = 0;
	else {
		weight = LevelWeight(pMonster);
		damage = int((((rand() % 5 + 50) * GetSTR() + mWeaponATK) / pMonster->GetDEF()) * weight);
	}

	pMonster->SetDamage(damage);
	if (damage == 0)
		sprintf(result, "������ ���������ϴ�!");
	else if (pMonster->GetLive())
		sprintf(result, "%s���� %d��ŭ�� ���ظ� �������ϴ�! [HP: %d / %d]",
			pMonster->GetName(), damage, pMonster->GetHP(), pMonster->GetMaxHP());
	else {
		sprintf(result, "%s�� �������� %s��(��) %d�� ���ظ� �԰� �׾����ϴ�!", GetName(), pMonster->GetName(), damage);
		killCount++;
		strcat(result, Loot(pMonster));
	}

	return result;
}

//��ų ����
string CUser::SkillActivate(CObject* pMonster) {
	int key, mp;

	while (1) {
		key = getch();

		switch (key) {
		case ESC:
			return "0";

		case A_KEY:
			if (skill[0]) {
				if (GetMP() >= TRIPLE_ATTACK_MP)
					return TripleAttack(pMonster, TRIPLE_ATTACK_MP);
				else
					continue;
			}
			else {
				continue;
			}
			break;

		case S_KEY:
			if (skill[1]) {
				mp = (GetMaxMP() / 10) * RECOVERY_MP;
				if (GetMP() >= mp)
					return Recovery(mp);
				else
					continue;
			}
			else {
				continue;
			}
			break;

		case D_KEY:
			if (skill[2]) {
				mp = (GetMaxMP() / 10) * TRUE_ATTACK_MP;
				if (GetMP() >= mp)
					return TrueAttack(pMonster, mp);
				else
					continue;
			}
			else {
				continue;
			}
			break;

		case F_KEY:
			if (skill[3]) {
				mp = (GetMaxMP() / 10) * AURA_BLADE_MP;
				if (GetMP() >= mp)
					return AuraBlade(pMonster, mp);
				else
					continue;
			}
			else {
				continue;
			}
			break;

		default:
			continue;
		}
	}

}

//���� ��������
bool CUser::AttackFail(CObject* pMonster) {
	bool attack_failed;
	int avoid;
	avoid = pMonster->GetDEX() + pMonster->GetLevel() - GetLevel() - mAccuracy;
	if (avoid <= 0) attack_failed = false;
	else {
		if (rand() % 10 < avoid / 10) attack_failed = true;
		else attack_failed = 0;
	}
	return attack_failed;
}

//��ų
string CUser::TripleAttack(CObject* pMonster, int mp) {
	char result[300] = "[��ų] Ʈ���� ����\n", tmp[100];
	int damage;
	bool attack_failed;
	float weight;

	UseMP(mp);		//MP�Ҹ�

	for (int i = 0; i < 3; i++) {
		attack_failed = AttackFail(pMonster);
		if (attack_failed) damage = 0;
		else {
			weight = LevelWeight(pMonster);
			damage = int((((rand() % 5 + 50) * (GetSTR() + TRIPLE_ATTACK) + mWeaponATK) / pMonster->GetDEF()) * weight);
		}

		pMonster->SetDamage(damage);
		if (damage == 0)
			switch (i) {
			case 0:
				sprintf(tmp, " [[�ϰ�]] ���������ϴ�!");
				break;
			case 1:
				sprintf(tmp, " [[�̰�]] ���������ϴ�!");
				break;
			case 2:
				sprintf(tmp, " [[���]] ���������ϴ�!");
				break;
			}
		else if (pMonster->GetLive())
			switch (i) {
			case 0:
				sprintf(tmp, " [[�ϰ�]] %s���� %d��ŭ�� ���ظ� �������ϴ�! [HP: %d / %d]",
					pMonster->GetName(), damage, pMonster->GetHP(), pMonster->GetMaxHP());
				break;
			case 1:
				sprintf(tmp, " [[�̰�]] %s���� %d��ŭ�� ���ظ� �������ϴ�! [HP: %d / %d]",
					pMonster->GetName(), damage, pMonster->GetHP(), pMonster->GetMaxHP());
				break;
			case 2:
				sprintf(tmp, " [[���]] %s���� %d��ŭ�� ���ظ� �������ϴ�! [HP: %d / %d]",
					pMonster->GetName(), damage, pMonster->GetHP(), pMonster->GetMaxHP());
				break;
			}

		else {
			switch (i) {
			case 0:
				sprintf(tmp, " [[�ϰ�]] %s��(��) %d�� ���ظ� �԰� �׾����ϴ�!", pMonster->GetName(), damage);
				killCount++;
				break;
			case 1:
				sprintf(tmp, " [[�̰�]] %s��(��) %d�� ���ظ� �԰� �׾����ϴ�!", pMonster->GetName(), damage);
				killCount++;
				break;
			case 2:
				sprintf(tmp, " [[���]] %s��(��) %d�� ���ظ� �԰� �׾����ϴ�!", pMonster->GetName(), damage);
				killCount++;
				break;
			}
			strcat(result, tmp);
			strcat(result, Loot(pMonster));
			break;
		}

		strcat(result, tmp);
		strcat(result, "\n");
	}
	return result;
}
string CUser::Recovery(int mp) {
	char result[100] = "[��ų] ȸ��\n", tmp[100];
	int recovery, reHP;

	UseMP(mp);

	recovery = (GetMaxHP() / 10) * RECOVERY;	//3�� ȸ��
	if (GetHP() + recovery >= GetMaxHP()) reHP = GetMaxHP();
	else reHP = GetHP() + recovery;

	SetHP(reHP);

	sprintf(tmp, " ȸ���� ������� %d�� ������ ȸ���մϴ�!", recovery);
	strcat(result, tmp);

	return result;
}
string CUser::TrueAttack(CObject* pMonster, int mp) {
	char result[300] = "[��ų] Ʈ�� ����\n", tmp[100];
	int damage;
	bool attack_failed;
	float weight;

	UseMP(mp);

	attack_failed = AttackFail(pMonster);
	if (attack_failed) damage = 0;
	else {
		weight = LevelWeight(pMonster);
		damage = int((((rand() % 5 + 30) * (GetSTR() + TRUE_ATTACK) + mWeaponATK)) * weight);
	}

	pMonster->SetDamage(damage);
	if (damage == 0)
		sprintf(tmp, " ������ ���������ϴ�!");
	else if (pMonster->GetLive())
		sprintf(tmp, " ���� ���� ġ��Ÿ!!\n %s���� %d��ŭ�� ���ظ� �������ϴ�! [HP: %d / %d]",
			pMonster->GetName(), damage, pMonster->GetHP(), pMonster->GetMaxHP());
	else {
		sprintf(tmp, " ġ������ �ϰ�!!\n %s��(��) ����߽��ϴ�!!", pMonster->GetName());
		killCount++;
		strcat(result, tmp);
		strcat(result, Loot(pMonster));
		return result;
	}
	strcat(result, tmp);
	return result;
}
string CUser::AuraBlade(CObject* pMonster, int mp) {
	char result[300] = "[��ų] ���� ���̵�\n", tmp[100];
	int damage;
	bool attack_failed;
	float weight;

	UseMP(mp);

	attack_failed = AttackFail(pMonster);
	if (attack_failed) damage = 0;
	else {
		weight = LevelWeight(pMonster);
		damage = int((((rand() % 5 + 50) * (GetSTR() + AURA_BLADE) + mWeaponATK) / pMonster->GetDEF()) * weight);
	}

	pMonster->SetDamage(damage);
	if (damage == 0)
		sprintf(tmp, " ������ ���������ϴ�!");
	else if (pMonster->GetLive())
		sprintf(tmp, " ���� ���̵�� %s���� %d��ŭ�� ���ظ� �������ϴ�! [HP: %d / %d]",
			pMonster->GetName(), damage, pMonster->GetHP(), pMonster->GetMaxHP());
	else {
		sprintf(tmp, " ġ������ �ϰ�!!\n %s��(��) ����߽��ϴ�!!", pMonster->GetName());
		killCount++;
		strcat(result, tmp);
		strcat(result, Loot(pMonster));
		return result;
	}
	strcat(result, tmp);
	return result;
}

char* CUser::Loot(CObject* pMonster) {
	char result[100];
	int gold;
	CMonster* pM = dynamic_cast<CMonster*>(pMonster);
	mExp += pM->GetMonsterExp();
	while (!(mExp < mTotalExp)) {
		LevelUp();
	}
	gold = pM->GetMonsterGold();
	mGold += gold;
	if (rand() % 100 < pM->GetItemWeight()) {
		mItem++;
		sprintf(result, "\n [%d��� ȹ��!] [��ȭ�� ȹ��!]\n", gold);
	}
	else sprintf(result, "\n [%d��� ȹ��!]\n", gold);

	return result;
}

void CUser::LevelUp() {
	int tmp;
	SetLevel(GetLevel() + 1);
	switch (GetLevel()) {
	case 10:
		skill[0] = true;
		break;
	case 20:
		skill[1] = true;
		break;
	case 30:
		skill[2] = true;
		break;
	case 40:
		skill[3] = true;
		break;
	}

	tmp = GetMaxHP();
	SetMaxHP(tmp + GetLevel() * 50);
	SetHP(GetMaxHP());

	tmp = GetMaxMP();
	SetMaxMP(tmp + GetLevel() * 50);
	SetMP(GetMaxMP());

	SetSTR(GetSTR() + 1);
	SetDEX(GetDEX() + 1);
	SetDEF(GetDEF() + 1);

	mAccuracy++;
	mExp = mExp - mTotalExp;
	mPoint += 5;
	mTotalExp += mTotalExp / 10;
}

void CUser::AutoRecovery() {
	int tmp;
	tmp = GetHP() + mAccuracy;
	if (tmp > GetMaxHP())
		SetHP(GetMaxHP());
	else
		SetHP(tmp);

	tmp = GetMP() + mAccuracy;
	if (tmp > GetMaxMP())
		SetMP(GetMaxMP());
	else
		SetMP(tmp);
}

void CUser::LoseExp() {
	int tmp = (mTotalExp / 10) * 3;
	if (mExp < tmp) mExp = 0;
	else mExp -= tmp;
}