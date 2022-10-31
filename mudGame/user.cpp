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

//일반 공격
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
		sprintf(result, "공격이 빗나갔습니다!");
	else if (pMonster->GetLive())
		sprintf(result, "%s에게 %d만큼의 피해를 입혔습니다! [HP: %d / %d]",
			pMonster->GetName(), damage, pMonster->GetHP(), pMonster->GetMaxHP());
	else {
		sprintf(result, "%s의 공격으로 %s이(가) %d의 피해를 입고 죽었습니다!", GetName(), pMonster->GetName(), damage);
		killCount++;
		strcat(result, Loot(pMonster));
	}

	return result;
}

//스킬 선택
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

//공격 성공여부
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

//스킬
string CUser::TripleAttack(CObject* pMonster, int mp) {
	char result[300] = "[스킬] 트리플 어택\n", tmp[100];
	int damage;
	bool attack_failed;
	float weight;

	UseMP(mp);		//MP소모

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
				sprintf(tmp, " [[일격]] 빗나갔습니다!");
				break;
			case 1:
				sprintf(tmp, " [[이격]] 빗나갔습니다!");
				break;
			case 2:
				sprintf(tmp, " [[삼격]] 빗나갔습니다!");
				break;
			}
		else if (pMonster->GetLive())
			switch (i) {
			case 0:
				sprintf(tmp, " [[일격]] %s에게 %d만큼의 피해를 입혔습니다! [HP: %d / %d]",
					pMonster->GetName(), damage, pMonster->GetHP(), pMonster->GetMaxHP());
				break;
			case 1:
				sprintf(tmp, " [[이격]] %s에게 %d만큼의 피해를 입혔습니다! [HP: %d / %d]",
					pMonster->GetName(), damage, pMonster->GetHP(), pMonster->GetMaxHP());
				break;
			case 2:
				sprintf(tmp, " [[삼격]] %s에게 %d만큼의 피해를 입혔습니다! [HP: %d / %d]",
					pMonster->GetName(), damage, pMonster->GetHP(), pMonster->GetMaxHP());
				break;
			}

		else {
			switch (i) {
			case 0:
				sprintf(tmp, " [[일격]] %s이(가) %d의 피해를 입고 죽었습니다!", pMonster->GetName(), damage);
				killCount++;
				break;
			case 1:
				sprintf(tmp, " [[이격]] %s이(가) %d의 피해를 입고 죽었습니다!", pMonster->GetName(), damage);
				killCount++;
				break;
			case 2:
				sprintf(tmp, " [[삼격]] %s이(가) %d의 피해를 입고 죽었습니다!", pMonster->GetName(), damage);
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
	char result[100] = "[스킬] 회복\n", tmp[100];
	int recovery, reHP;

	UseMP(mp);

	recovery = (GetMaxHP() / 10) * RECOVERY;	//3할 회복
	if (GetHP() + recovery >= GetMaxHP()) reHP = GetMaxHP();
	else reHP = GetHP() + recovery;

	SetHP(reHP);

	sprintf(tmp, " 회복의 기운으로 %d의 생명을 회복합니다!", recovery);
	strcat(result, tmp);

	return result;
}
string CUser::TrueAttack(CObject* pMonster, int mp) {
	char result[300] = "[스킬] 트루 어택\n", tmp[100];
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
		sprintf(tmp, " 공격이 빗나갔습니다!");
	else if (pMonster->GetLive())
		sprintf(tmp, " 방어력 무시 치명타!!\n %s에게 %d만큼의 피해를 입혔습니다! [HP: %d / %d]",
			pMonster->GetName(), damage, pMonster->GetHP(), pMonster->GetMaxHP());
	else {
		sprintf(tmp, " 치명적인 일격!!\n %s이(가) 즉사했습니다!!", pMonster->GetName());
		killCount++;
		strcat(result, tmp);
		strcat(result, Loot(pMonster));
		return result;
	}
	strcat(result, tmp);
	return result;
}
string CUser::AuraBlade(CObject* pMonster, int mp) {
	char result[300] = "[스킬] 오러 블레이드\n", tmp[100];
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
		sprintf(tmp, " 공격이 빗나갔습니다!");
	else if (pMonster->GetLive())
		sprintf(tmp, " 오러 블레이드로 %s에게 %d만큼의 피해를 입혔습니다! [HP: %d / %d]",
			pMonster->GetName(), damage, pMonster->GetHP(), pMonster->GetMaxHP());
	else {
		sprintf(tmp, " 치명적인 일격!!\n %s이(가) 즉사했습니다!!", pMonster->GetName());
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
		sprintf(result, "\n [%d골드 획득!] [강화석 획득!]\n", gold);
	}
	else sprintf(result, "\n [%d골드 획득!]\n", gold);

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