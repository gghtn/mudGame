#include "user.h"
#include <stdlib.h>
#include <time.h>

CUser::CUser(string name) :CObject() { 
	mb_normalAtk = true, mb_skillAtk = false;
	mWeaponATK = 100, mPoint = 0, mExp = 0, mTotalExp = 100, mGold = 0;
	skill = 0;
	
	SetInitAll(name);
}

string CUser::Attack(CObject* pObject) {
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
		damage = int((((rand()%20 + 80) * GetSTR() + mWeaponATK) / pObject->GetDEF()) * weight);
	}

	pObject->SetDamage(damage);
	if (damage == 0)
		sprintf(result, "%s�� ������ ���������ϴ�!", GetName());
	else if(pObject->GetLive())
		sprintf(result, "%s�� �������� %s���� %d��ŭ�� ���ظ� �������ϴ�!", GetName(), pObject->GetName(), damage);
	else sprintf(result, "%s�� �������� %s��(��) %d�� ���ظ� �԰� �׾����ϴ�!", GetName(), pObject->GetName(), damage);

	return result;
}