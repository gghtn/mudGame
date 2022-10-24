#include "monster.h"

string CMonster::Attack(CObject* pObject) {
	char result[100];
	int damage, avoid;
	float weight;

	weight = (float)GetLevel() - pObject->GetLevel();
	if (weight < -20 && weight > -100) weight = 1.0f + (weight / 100);
	else if (weight < -100) weight = 0.0f;
	else if (weight > 20) weight = 1.0f + (weight / 100);
	else weight = 1.0f;

	avoid = pObject->GetDEX() + pObject->GetLevel() - GetLevel();
	if (avoid <= 0) avoid = 0;
	else {
		if (rand() % 10 < avoid / 10) avoid = 1;
		else avoid = 0;
	}

	if (avoid) damage = 0;
	else {
		damage = int((((rand() % 50 + 10) * GetSTR()) / pObject->GetDEF()) * weight);
	}

	pObject->SetDamage(damage);
	if (damage == 0)
		sprintf(result, "%s의 공격을 회피했습니다!", GetName());
	else if (pObject->GetLive())
		sprintf(result, "%s의 공격으로 %d만큼의 피해를 입었습니다!", GetName(), damage);
	else sprintf(result, "%s의 공격으로 %s이(가) 죽었습니다!", GetName(), pObject->GetName());

	return result;
}