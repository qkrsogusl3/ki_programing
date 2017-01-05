#include "stdafx.h"
#include "GameManager.h"

#include <conio.h>//console and port I/O Ű�Է�
#include <Windows.h>
#include <iostream>

#include <time.h>
#include "ActorBulletPattern.h"

#include "EnemyFactorySample0.h"
#include "EnemyFactorySample1.h"
#include "EnemyFactorySample2.h"

#define SCREEN_SETTING false

CGameManager::CGameManager()
{
	srand((unsigned int)time(NULL));
	
	if(SCREEN_SETTING)
		system("mode con: cols=80 lines=24");

	mStateActions[CGameManager::STATE_INIT] = &CGameManager::Init;
	mStateActions[CGameManager::STATE_TITLE] = &CGameManager::Title;
	mStateActions[CGameManager::STATE_UPDATE] = &CGameManager::Update;
	mStateActions[CGameManager::STATE_DISPLAY] = &CGameManager::Display;
	mStateActions[CGameManager::STATE_QUIT] = &CGameManager::Quit;

	mCurrentState = CGameManager::STATE_INIT;

}

CGameManager::~CGameManager()
{

}


void CGameManager::Init()
{
	mActor.SetUp(WIDTH / 2, HEIGHT - 1);
	
	int ti = 0;
	//CActorBullet * tp = new CActorBullet();
	//tp->SetDirectionAndSpeedPower(0, -1, 1);
	//mActor.AddBullet(tp);
	CActorBulletPattern * tpActorBulletPattern = NULL;
	CActorBullet * tpActorBullet = NULL;
	for (ti = 0; ti < ACTOR_BULLET_COUNT; ti++)
	{
		tpActorBulletPattern = new CActorBulletPattern();
		
		//3���� ź
		tpActorBullet = new CActorBullet();
		tpActorBullet->SetDirectionAndSpeedPower(-1, -1, 2);
		tpActorBulletPattern->AddBullet(tpActorBullet);

		tpActorBullet = new CActorBullet();
		tpActorBullet->SetDirectionAndSpeedPower(0, -1, 2);
		tpActorBulletPattern->AddBullet(tpActorBullet);

		tpActorBullet = new CActorBullet();
		tpActorBullet->SetDirectionAndSpeedPower(1, -1, 2);
		tpActorBulletPattern->AddBullet(tpActorBullet);

		
		mActor.AddBullet(tpActorBulletPattern);
	}



	mEnemyFactorys.reserve(5);
	mEnemyFactorys.push_back(new CEnemyFactorySample0());
	mEnemyFactorys.push_back(new CEnemyFactorySample1());
	mEnemyFactorys.push_back(new CEnemyFactorySample2());

	SetFactory(0);

	if (mEnemyFactorys.size() > 0)
	{
		mCurrentState = CGameManager::STATE_TITLE;
	}
	else
	{
		mCurrentState = CGameManager::STATE_QUIT;
	}
}

void CGameManager::Title()
{
	cout << "��Ÿ����" << endl;
	Sleep(1000);
	mCurrentState = CGameManager::STATE_UPDATE;
}
void CGameManager::Update()
{
	mActor.Clean(*tPixel);
	int ti = 0;
	for (ti = 0; ti < mEnemys->size(); ti++)
	{
		(*mEnemys)[ti]->Clean(&tPixel[0][0]);
	}

	mKey = 0;
	if (0 != _kbhit())//�Էµ� Ű�� ������
	{
		mKey = _getch();//�Էµ� Ű�� �޾ƿ�

						//��������
		switch (mKey)
		{
		case 'Q':
		case 'q':
			mCurrentState = CGameManager::STATE_QUIT;
			return;
		case 'P':
		case 'p':
			SetFactory(mCurrentFactory + 1);
			break;
		}
	}

	mActor.Update();
	for (ti = 0; ti < mEnemys->size(); ti++)
	{
		if ((*mEnemys)[ti]->GetAlive() == true)
		{
			(*mEnemys)[ti]->Update();
			if ((*mEnemys)[ti]->GetX() < 0)
			{
				(*mEnemys)[ti]->SetX(0);
			}
			else if ((*mEnemys)[ti]->GetX() > WIDTH - 1)
			{
				(*mEnemys)[ti]->SetX(WIDTH - 1);
			}
		}
	}

	//Collision

	for (ti = 0; ti < mEnemys->size(); ti++)
	{
		if (true == mActor.DoCollisionBulletWithEnemy((*mEnemys)[ti]))
		{
			(*mEnemys)[ti]->SetAlive(false);
			break;
		}
		//todo : boss...
	}

	for (ti = 0; ti < mEnemys->size(); ti++)
	{
		if (mActor.GetAlive() && true == (*mEnemys)[ti]->DoCollisionBulletWithActor(&mActor))
		{
			mActor.SetAlive(false);
			break;
		}
		//todo : boss...
	}

	mCurrentState = CGameManager::STATE_DISPLAY;




	if (mActor.GetAlive() == false)
	{
		Sleep(500);
		system("cls");
		mActor.SetAlive(true);
		mCurrentState = CGameManager::STATE_TITLE;
	}
	for (ti = 0; ti < mEnemys->size(); ti++)
	{
		if ((*mEnemys)[ti]->GetAlive())
		{
			return;
		}
	}
	SetFactory(mCurrentFactory + 1);
}

void CGameManager::Display()
{

	ClearScreen(0, 0);

	if (mActor.GetAlive())
	{
		mActor.Display(*tPixel);
	}
	int ti = 0;
	for (ti = 0; ti < mEnemys->size(); ti++)
	{
		(*mEnemys)[ti]->Display(&tPixel[0][0]);
	}

	for (mRow = 0; mRow < HEIGHT; mRow++)
	{
		for (mCol = 0; mCol < WIDTH; mCol++)
		{
			cout << tPixel[mRow][mCol];
		}

		//if (SCREEN_SETTING)
			//cout << endl;
	}
	if (SCREEN_SETTING)
		Sleep(1000 / 30);

	mCurrentState = CGameManager::STATE_UPDATE;
}

void CGameManager::Quit()
{
	mIsPlaying = false;
	mEnemys = NULL;
	int ti = 0;
	for (int ti = 0; ti < mEnemyFactorys.size(); ti++)
	{
		mEnemyFactorys[ti]->Destroy();
	}

	mActor.Destroy();
	//delete ...
}


void CGameManager::Play()
{
	mIsPlaying = true;
	while (mIsPlaying)
	{
		(this->*mStateActions[mCurrentState])();
	}
}

void CGameManager::SetEnemys(vector<CEnemy*>* tpEnemys)
{
	mEnemys = tpEnemys;
}

void CGameManager::SetFactory(int tIndex)
{
	mCurrentFactory = tIndex;
	if (mCurrentFactory >= mEnemyFactorys.size())
	{
		mCurrentFactory = 0;
	}
	mEnemyFactorys[mCurrentFactory]->DoSetting(*this);
}

void CGameManager::ClearScreen(int tX, int tY)
{
	CONSOLE_CURSOR_INFO cci;
	CONSOLE_CURSOR_INFO cci_old;

	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleCursorInfo(hOutput, &cci_old);

	cci.bVisible = FALSE;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);

	COORD cd;
	cd.X = tX;
	cd.Y = tY;

	SetConsoleCursorPosition(hOutput, cd);
}

