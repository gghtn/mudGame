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
		sprintf(result, "%s�� ������ ȸ���߽��ϴ�!", GetName());
	else if (pObject->GetLive())
		sprintf(result, "%s�� �������� %d��ŭ�� ���ظ� �Ծ����ϴ�!", GetName(), damage);
	else sprintf(result, "%s�� �������� %s��(��) �׾����ϴ�!", GetName(), pObject->GetName());

	return result;
}