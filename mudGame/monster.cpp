#include "monster.h"

void CMonster::Init(string name, int weight, int status, int exp, int gold, int item) {
	int level = rand() % 10 + weight;
	SetName(name);
	SetLevel(level);
	SetMaxHP(100 * level);
	SetHP(GetMaxHP());
	SetSTR(rand() % 10 + status + level);
	SetDEX(rand() % 10 + status + level);
	SetDEF(rand() % 10 + status + level);
	SetMonsterInfo(exp + level * 10, gold + level * 10, item);
}

string CMonster::Attack(CObject* pUser) {
	char result[100];
	int damage, avoid;
	float weight;

	avoid = pUser->GetDEX() + pUser->GetLevel() - GetLevel();
	if (avoid <= 0) avoid = 0;
	else {
		if (rand() % 10 < avoid / 10) avoid = 1;
		else avoid = 0;
	}

	if (avoid) damage = 0;
	else {
		weight = LevelWeight(pUser);
		damage = int((((rand() % 10 + 20) * GetSTR()) / pUser->GetDEF()) * weight);
	}

	pUser->SetDamage(damage);
	if (damage == 0)
		sprintf(result, "%s의 공격을 회피했습니다!", GetName());
	else if (pUser->GetLive())
		sprintf(result, "%s의 공격으로 %d만큼의 피해를 입었습니다!", GetName(), damage);
	else sprintf(result, "%s의 공격으로 %s이(가) 죽었습니다!", GetName(), pUser->GetName());

	return result;
}