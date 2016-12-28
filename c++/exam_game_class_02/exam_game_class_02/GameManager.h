#pragma once
#include "MapManager.h"
#include "Player.h"
#include "Slime.h"
#include "BossSlime.h"

#include "defines.h"

class CGameManager
{
private:
	int mGameState = 0;//���ӽ��� �� Ÿ��Ʋ ����
	int mInput = 0;//Input�Է� �޴� ����
	char mIsContinue = 0;

	CMapManager mMap;
	CPlayer *mPlayer = NULL;
	CSlime *mNormalSlime = NULL;
	CBossSlie *mBossSlime = NULL;


public:
	CGameManager();
	~CGameManager();

	CPlayer& GetPlayer();
	CMonster& GetMonster(int tKind);
	void Play();


private:
	int DisplayTitle();

};

