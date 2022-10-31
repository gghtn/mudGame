#include "boss.h"
#pragma warning(disable:4996)

string CBoss::BossAttack(CObject* pUser) {
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
		damage = int((((rand() % 5 + 50) * GetSTR() + mbossATK) / pUser->GetDEF()) * weight);
	}

	// 1/5확률로 강한 공격
	if (rand() % 5 == 0) {
		damage *= 3;
		pUser->SetDamage(damage);
		if (damage == 0)
			sprintf(result, "%s의 공격을 회피했습니다!", GetName());
		else if (pUser->GetLive())
			sprintf(result, "%s이 스킬을 사용합니다\n 강한 공격이 적중해 %d만큼의 피해를 입었습니다!", GetName(), damage);
		else sprintf(result, "%s이 스킬을 사용합니다\n 치명적인 공격으로 %s이(가) 죽었습니다!", GetName(), pUser->GetName());
	}
	else {
		pUser->SetDamage(damage);
		if (damage == 0)
			sprintf(result, "%s의 공격을 회피했습니다!", GetName());
		else if (pUser->GetLive())
			sprintf(result, "%s의 공격으로 %d만큼의 피해를 입었습니다!", GetName(), damage);
		else sprintf(result, "%s의 공격으로 %s이(가) 죽었습니다!", GetName(), pUser->GetName());
	}

	return result;
}