#include "stdafx.h"
#include "GameManager.h"

#include <iostream>

using namespace std;

CGameManager::CGameManager()
{
	mGameState = TITLE;//���ӽ��� �� Ÿ��Ʋ ����
	mInput = 0;//Input�Է� �޴� ����
	mIsContinue = YES;

	mCharacterFactory.SetState(CCharacterFactory::STATE_PLAYER);
	mPlayer = (CPlayer*)mCharacterFactory.Execute();

	mCharacterFactory.SetState(CCharacterFactory::STATE_SLIME);
	mNormalSlime = (CSlime*)mCharacterFactory.Execute();

	mCharacterFactory.SetState(CCharacterFactory::STATE_BOSS_SLIME);
	mBossSlime = (CBossSlie*)mCharacterFactory.Execute();
}


CGameManager::~CGameManager()
{
	//�� �����Ҵ� ������ �ʱ�ȭ
	if (mPlayer != NULL)
	{
		delete mPlayer;
		mPlayer = NULL;
	}
	if (mNormalSlime != NULL)
	{
		delete mNormalSlime;
		mNormalSlime = NULL;
	}
	if (mBossSlime != NULL)
	{
		delete mBossSlime;
		mBossSlime = NULL;
	}
}


CPlayer & CGameManager::GetPlayer()
{
	return *mPlayer;
}

CMonster & CGameManager::GetMonster(int tKind)
{
	if (tKind == KIND_NORMAL_SLIME)
		return *mNormalSlime;
	else
		return *mBossSlime;
}

int CGameManager::DisplayTitle()
{
	int tInput = 0;

	printf("\n\n\t");
	printf("[ ���� ������ ]");
	printf("\n\n\n");

	printf("1.���� ����");
	printf("\n");
	printf("2.����");
	printf("\n");

	cin >> tInput;

	if (tInput == 1)//���� ���� �� ���¸� �ʱ�ȭ�� ����
	{
		tInput = INIT;
	}
	else//����
	{
		tInput = QUIT;
	}

	return tInput;
}

void CGameManager::Play()
{
	while (NO != mIsContinue)
	{
		switch (mGameState)
		{
		case TITLE://Ÿ��Ʋ
			mGameState = DisplayTitle();
			break;
		case INIT://����� �� �ʱ�ȭ ��
			mPlayer->SetHealth(5);
			mPlayer->SetCurrentHealth(mPlayer->GetHealth());
			mPlayer->SetPower(1);

			mNormalSlime->SetHealth(5);
			mNormalSlime->SetCurrentHealth(mNormalSlime->GetHealth());
			mNormalSlime->SetPower(1);

			mBossSlime->SetHealth(10);
			mBossSlime->SetCurrentHealth(mBossSlime->GetHealth());
			mBossSlime->SetPower(2);


			//�÷��̾� �ʱ���ġ�� �̵�
			mPlayer->DoMove(mMap.GetMap(), 0);
			//2������ �Ϲ� �������� �ִ�. 
			mMap.GetMap()[2] = KIND_NORMAL_SLIME;
			//4������ ���� �������� �ִ�.
			mMap.GetMap()[4] = KIND_BOSS_SLIME;


			mGameState = PLAY;
			break;
		case PLAY:
			mMap.DrawMap();

			if (mMap.CheckSlimeEncount(mPlayer))//���� ����ħ
			{
				int tSlimeKind = 0;
				CMonster *tMonster = NULL;

				//���� �÷��̾� ��ġ+1�� ���ֺ��� ������ ����
				tSlimeKind = mMap.GetMap()[mPlayer->GetPosition() + 1];

				if (tSlimeKind == KIND_NORMAL_SLIME)
				{
					printf("\t");
					printf("[ �Ϲ� �������� ��Ÿ����. ]");
					printf("\n\n");
					tMonster = mNormalSlime;
				}
				else if (tSlimeKind == KIND_BOSS_SLIME)
				{
					printf("\t");
					printf("[ ���� �������� ��Ÿ����. ]");
					printf("\n\n");
					tMonster = mBossSlime;
				}

				printf("1.�ο��� �Ǵ�!!");
				printf("\n");
				printf("2.����ģ��..");
				printf("\n");
				cin >> mInput;

				if (mInput == 1)
				{
					int tBattleResult = 0;
					//printf("\t[ ������ �����ߴ�!! ]\n\n");

					tBattleResult = tMonster->DoBattle(/*this, */mPlayer);

					if (tBattleResult == 1)//�¸�
					{
						//��� ü�� ȸ��
						mPlayer->SetCurrentHealth(mPlayer->GetHealth());

						//�������� �ִ� ��ġ �ʱ�ȭ
						mMap.GetMap()[mPlayer->GetPosition() + 1] = 0;
						//���� ��ġ�� �̵�
						mPlayer->DoMove(mMap.GetMap(), mPlayer->GetPosition() + 1);
					}
					else if (tBattleResult == 0)//�й�
					{
						printf("\n\n\t\t");
						printf("[ ���� �׾���... ]");
						printf("\n\n\n");

						mGameState = QUIT;
					}

					printf("Input Any Key");
					printf("\n");
					cin >> mInput;
				}
				else if (mInput == 2)
				{
					printf("\t");
					printf("[ ���� �����ƴ�... ]");
					printf("\n");

					mPlayer->DoMove(mMap.GetMap(), mPlayer->GetPosition() - 1);

				}
			}
			else//���� ����ġ�� ����
			{
				if (mPlayer->GetPosition() != MAP_LENGTH - 1)//�� ���� �������� �ʾ�����
				{
					printf("\t");
					printf("[ ��� �ұ�? ]");
					printf("\n\n");
					printf("1.�����ϱ�");
					printf("\n");
					printf("2.���ư���");
					printf("\n");


					cin >> mInput;

					if (mInput == 1)
					{
						mPlayer->DoMove(mMap.GetMap(), mPlayer->GetPosition() + 1);

					}
					else if (mInput == 2)
					{
						mPlayer->DoMove(mMap.GetMap(), mPlayer->GetPosition() - 1);
					}
				}
				else
				{
					printf("\t");
					printf("[ ������ Ŭ�����Ͽ����ϴ�. ]");
					printf("\n\n");
					printf("Input Any Key");
					printf("\n");

					cin >> mInput;
					mGameState = QUIT;
				}
			}

			break;
		case QUIT://����
			printf("\n\n\n");
			printf("����Ͻðڽ��ϱ�?(y/n): ");
			cin >> mIsContinue;
			if (YES == mIsContinue)
			{
				mGameState = 0;
			}
			break;
		}
		system("cls");
	}
}

