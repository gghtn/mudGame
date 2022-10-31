#pragma once
#include <conio.h>
#include "console.h"
#include "doublebuffer.h"
#include "key_pos.h"
#include "object.h"
#include "boss.h"
#include "user.h"

#define MAX_PRINT 2000

class CDungeon {
	string mDungeonName;
	char mPrint[MAX_PRINT];	//���� ��¹�
	int mMonsterCount;		//���� ��
	bool mbExit, mbBoss;
	CObject* pO;
	CUser* pU;
public:
	CDungeon(CObject*);
	virtual ~CDungeon() {}

	virtual void DungeonStart() = 0;		//�ν���Ʈ ���� ����
	void Battle(CObject** p);				//���� ����

	void Render(int, bool is_skill = 0);	//�����Լ�
	void ExitRender();						//���� ���� Ż��� �����Լ�
	void Select(CObject*);					//���� ����̽� ����(�⺻����, ��ų����)
	bool UserTrun(CObject*, int pos_x);		//���� ������
	void MonsterTrun(CObject*);				//�Ϲ� ���� ������
	void BossTrun(CObject* p);				//���� ���� ������

	void InitPrint() { memset(mPrint,'\0',MAX_PRINT); }	//mPrint �ʱ�ȭ

	void SetDungeonName(string name) { mDungeonName = name; }
	void SetMonsterCount(int num) { mMonsterCount = num; }
	void SetIsBoss() { mbBoss = true; }

	int GetMonsterCount() { return mMonsterCount; }
	
};