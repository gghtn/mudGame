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
	char mPrint[MAX_PRINT];	//던전 출력문
	int mMonsterCount;		//몬스터 수
	bool mbExit, mbBoss;
	CObject* pO;
	CUser* pU;
public:
	CDungeon(CObject*);
	virtual ~CDungeon() {}

	virtual void DungeonStart() = 0;		//인스턴트 던전 시작
	void Battle(CObject** p);				//전투 시작

	void Render(int, bool is_skill = 0);	//렌더함수
	void ExitRender();						//던전 도중 탈출시 렌더함수
	void Select(CObject*);					//유저 디바이스 선택(기본공격, 스킬공격)
	bool UserTrun(CObject*, int pos_x);		//유저 공격턴
	void MonsterTrun(CObject*);				//일반 몬스터 공격턴
	void BossTrun(CObject* p);				//보스 몬스터 공격턴

	void InitPrint() { memset(mPrint,'\0',MAX_PRINT); }	//mPrint 초기화

	void SetDungeonName(string name) { mDungeonName = name; }
	void SetMonsterCount(int num) { mMonsterCount = num; }
	void SetIsBoss() { mbBoss = true; }

	int GetMonsterCount() { return mMonsterCount; }
	
};