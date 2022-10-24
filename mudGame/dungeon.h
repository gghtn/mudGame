#pragma once
#include <conio.h>
#include "console.h"
#include "doublebuffer.h"
#include "key_pos.h"
#include "object.h"
#include "user.h"


#include "scarecrow.h"

#define MAX_PRINT 2000

class CDungeon {
	string mDungeonName;
	char mPrint[MAX_PRINT];	//���� ��¹�
	CObject* pO;
	CUser* pU;
public:
	CDungeon(CObject*);

	void DungeonStart();

	void Render(int);
	void UserAttack(CObject*);
	void MonsterAttack(CObject*);

	void InitPrint() { memset(mPrint,'\0',MAX_PRINT); }	//mPrint �ʱ�ȭ

	void SetDungeonName(string name) { mDungeonName = name; }
};