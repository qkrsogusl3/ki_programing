#include "stdafx.h"
#include <iostream>

#include <stdlib.h>
#include <time.h>

#define YES 'y'
#define NO 'n'

//State Values
#define TITLE 0
#define INIT 1
#define PLAY 2
#define QUIT 3

//Player,Monsters Kind
#define KIND_PLAYER 11
#define KIND_NORMAL_SLIME 12
#define KIND_BOSS_SLIME 13

#define MAP_LENGTH 5
#define MAX_HEALTH 10

using namespace std;

class CPlayer
{
private:
	int mHealth = 0;
	int mCurrentHealth = 0;
	int mPower = 0;
	int mPosition = 0;

public:
	CPlayer();
	~CPlayer();
	//getter
	int GetHealth();
	int& GetCurrentHealth();
	int& GetPower();
	int GetPosition();
	//setter
	void SetHealth(int tHealth);
	void SetCurrentHealth(int tCurHealth);
	void SetPower(int tPower);
	void SetPosition(int tPosition);
	
	void DoMove(int tMap[], int tIndex);

};

class CSlime
{
private:
	int mHealth = 0;
	int mCurrentHealth = 0;
	int mPower = 0;
public:
	//char(*mDoBattle)(CPlayer *tPlayer, CSlime *tSlime) = NULL;

	//getter
	int GetHealth();
	int& GetCurrentHealth();
	int& GetPower();
	//setter
	void SetHealth(int tHealth);
	void SetCurrentHealth(int tCurHealth);
	void SetPower(int tPower);
};

class CMap
{
private:
	int mMap[MAP_LENGTH] = { 0 };//������ �ʱ��̷� ��ҵ� �ʱ�ȭ

public:
	void DrawMap();
	int* GetMap();
	char CheckSlimeEncount(CPlayer *tPlayer);
};

class CDice
{
private:
	int mDiceNumber = 0;
public:
	int DoThrow(int tMaxNumber);
	int GetDiceNumber();
};

class CNormalBattle
{
private:
	int tInput = 0;
	char tResult = 0;

	CDice tDice;
public:
	char DoBattle(CPlayer *tPlayer, CSlime *tSlime);
	void DoAttack(int &tPower, int &tTargetHealth);
};

class CBossBattle
{
private:
	int tPlayerCard = 0;
	int tCompareResult = 0;

	char tResult = 0;
	CDice tSlimeDice;
public:
	char DoBattle(CPlayer *tPlayer, CSlime *tSlime);
	char CheckCompareCard(int tPlayerCard, int tSlimeCard);
	void DisplayCard(int tCardValue);
	void DoAttack(int &tPower, int &tTargetHealth);
};

class CGameManager
{
private:
	int mGameState = 0;//���ӽ��� �� Ÿ��Ʋ ����
	int mInput = 0;//Input�Է� �޴� ����
	char mIsContinue = 0;

	CMap mMap;
	CPlayer *mPlayer = NULL;
	CSlime *mNormalSlime = NULL;
	CSlime *mBossSlime = NULL;

	CNormalBattle mNormalBattle;
	CBossBattle mBossBattle;
public:
	CGameManager();
	~CGameManager();

	CPlayer& GetPlayer();
	CSlime& GetSlime(int tKind);

	int DisplayTitle();
	void Play();
	char GetIsContinue();
};


void DisplayGauge(int tCurrentValue, int tMaxValue);


int main()
{

	srand(time(NULL));//���� �õ� ����

	CGameManager tGameManager;

	tGameManager.Play();

	return 0;
}

//Ÿ��Ʋ ȭ���� �׸��� 
//����,���Ḧ �Է¹޴´�.
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

//�÷��̾��� ��ġ������ �����ϰ�
//���� ��ġ ������ �����Ѵ�.
//void PlayerToMove(Player *tPlayer, int tMap[], int tIndex)
//{
//	if (tIndex >= 0 && tIndex < MAP_LENGTH)
//	{
//		tMap[tPlayer->GetPosition()] = 0;
//		tMap[tIndex] = KIND_PLAYER;
//		tPlayer->SetPosition(tIndex);
//	}
//	else
//	{
//		int tInput = 0;
//
//		printf("\t");
//		printf("[ �̵� �� �� ����... ]");
//		printf("\n");
//		printf("Input Any Key");
//		printf("\n");
//		cin >> tInput;
//	}
//
//}

//������ �� ���¸� �׸���.
void CMap::DrawMap()
{
	int ti = 0;

	printf("====================================");
	printf("====================================");
	printf("\n");
	printf("==");
	for (ti = 0; ti < MAP_LENGTH; ti++)
	{
		switch (mMap[ti])
		{
		case KIND_PLAYER:
			printf("[  PLAYER  ]==");
			break;
		case KIND_NORMAL_SLIME:
			printf("[  SLIME   ]==");
			break;
		case KIND_BOSS_SLIME:
			printf("[BOSS SLIME]==");
			break;
		case 0://����
		default:
			printf("[          ]==");
			break;
		}
	}
	printf("\n");
	printf("====================================");
	printf("====================================");
	printf("\n\n");

}

int * CMap::GetMap()
{
	return mMap;
}

//�÷��̾ ���� ���ֺ��� �ִ��� �˻��Ѵ�.
char CMap::CheckSlimeEncount(CPlayer *tPlayer)
{
	char tResult = 0;

	if (tPlayer != NULL && tPlayer->GetPosition() < MAP_LENGTH - 1)
	{
		if (mMap[tPlayer->GetPosition() + 1] != 0)
		{
			tResult = 1;
		}
	}
	return tResult;
}


//�ֻ����� ���� ������ �����Ѵ�.
int CDice::DoThrow(int tMaxNumber)
{
	mDiceNumber = rand() % tMaxNumber + 1;

	return mDiceNumber;
}

int CDice::GetDiceNumber()
{
	return mDiceNumber;
}

//�÷��̾�� �������� �и� ���Ͽ� ����� �����Ѵ�.
char CBossBattle::CheckCompareCard(int tPlayerCard, int tSlimeCard)
{
	char tResult = 0;

	switch (tPlayerCard)
	{
	case 1://����
		switch (tSlimeCard)
		{
		case 1:
			tResult = 0;
			break;
		case 2:
			tResult = 2;
			break;
		case 3:
			tResult = 1;
			break;
		}
		break;
	case 2://����
		switch (tSlimeCard)
		{
		case 1:
			tResult = 1;
			break;
		case 2:
			tResult = 0;
			break;
		case 3:
			tResult = 2;
			break;
		}
		break;
	case 3://��
		switch (tSlimeCard)
		{
		case 1:
			tResult = 2;
			break;
		case 2:
			tResult = 1;
			break;
		case 3:
			tResult = 0;
			break;
		}
		break;
	}

	return tResult;
}
//�� ���� �´� �ؽ�Ʈ�� ����Ѵ�.
void CBossBattle::DisplayCard(int tCardValue)
{
	switch (tCardValue)
	{
	case 1:
		printf("����");
		break;
	case 2:
		printf("����");
		break;
	case 3:
		printf("��");
		break;
	}
}

//���簪�� �ִ밪�� �Է¹޾� �������� ����Ѵ�.
void DisplayGauge(int tCurrentValue, int tMaxValue)
{
	int ti = 0;

	for (ti = 0; ti < tCurrentValue; ti++)
	{
		printf("��");
	}
	for (ti = 0; ti < tMaxValue - tCurrentValue; ti++)
	{
		printf("��");
	}

}



#pragma region Player ����

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

int CPlayer::GetHealth()
{
	return mHealth;
}
void CPlayer::SetHealth(int tHealth)
{
	mHealth = tHealth;
}
int& CPlayer::GetCurrentHealth()
{
	return mCurrentHealth;
}
void CPlayer::SetCurrentHealth(int tCurHealth)
{
	mCurrentHealth = tCurHealth;
}
int& CPlayer::GetPower()
{
	return mPower;
}
void CPlayer::SetPower(int tPower)
{
	mPower = tPower;
}
int CPlayer::GetPosition()
{
	return mPosition;
}
void CPlayer::SetPosition(int tPosition)
{
	mPosition = tPosition;
}

void CPlayer::DoMove(int tMap[], int tIndex)
{
	if (tIndex >= 0 && tIndex < MAP_LENGTH)
	{
		tMap[mPosition] = 0;
		tMap[tIndex] = KIND_PLAYER;
		mPosition = tIndex;
	}
	else
	{
		int tInput = 0;

		printf("\t");
		printf("[ �̵� �� �� ����... ]");
		printf("\n");
		printf("Input Any Key");
		printf("\n");
		cin >> tInput;
	}
}
#pragma endregion

#pragma region Slime ����

int CSlime::GetHealth()
{
	return mHealth;
}
int& CSlime::GetCurrentHealth()
{
	return mCurrentHealth;
}
int& CSlime::GetPower()
{
	return mPower;
}
void CSlime::SetHealth(int tHealth)
{
	mHealth = tHealth;
}
void CSlime::SetCurrentHealth(int tCurHealth)
{
	mCurrentHealth = tCurHealth;
}
void CSlime::SetPower(int tPower)
{
	mPower = tPower;
}



#pragma endregion

CGameManager::CGameManager()
{
	mGameState = TITLE;//���ӽ��� �� Ÿ��Ʋ ����
	mInput = 0;//Input�Է� �޴� ����
	mIsContinue = YES;

	mPlayer = new CPlayer();
	mNormalSlime = new CSlime();
	mBossSlime = new CSlime();

	//mNormalSlime->mDoBattle = mNormalBattle.DoBattle;//�ֻ��� ����
	//mBossSlime->mDoBattle = mBossBattle.DoBattle;//����,����,��

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

CSlime & CGameManager::GetSlime(int tKind)
{
	if (tKind == KIND_NORMAL_SLIME)
		return *mNormalSlime;
	else
		return *mBossSlime;
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
				CSlime *tSlime = NULL;

				//���� �÷��̾� ��ġ+1�� ���ֺ��� ������ ����
				tSlimeKind = mMap.GetMap()[mPlayer->GetPosition() + 1];

				if (tSlimeKind == KIND_NORMAL_SLIME)
				{
					printf("\t");
					printf("[ �Ϲ� �������� ��Ÿ����. ]");
					printf("\n\n");
					tSlime = mNormalSlime;
				}
				else if (tSlimeKind == KIND_BOSS_SLIME)
				{
					printf("\t");
					printf("[ ���� �������� ��Ÿ����. ]");
					printf("\n\n");
					tSlime = mBossSlime;
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

					if (tSlimeKind == KIND_NORMAL_SLIME)
					{
						tBattleResult = mNormalBattle.DoBattle(mPlayer, tSlime);
					}
					else if (tSlimeKind == KIND_BOSS_SLIME)
					{
						tBattleResult = mBossBattle.DoBattle(mPlayer, tSlime);
					}

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

char CGameManager::GetIsContinue()
{
	return mIsContinue;
}

char CNormalBattle::DoBattle(CPlayer * tPlayer, CSlime * tSlime)
{
	while (1)
	{
		printf("\t");
		printf("[���]");
		DisplayGauge(tPlayer->GetCurrentHealth(), tPlayer->GetHealth());
		printf(" VS ");
		printf("[������]");
		DisplayGauge(tSlime->GetCurrentHealth(), tSlime->GetHealth());
		printf("\n\n");

		printf("1. �ֻ����� ������.");
		printf("\n");
		cin >> tInput;

		printf("================================================");
		printf("\n\n");

		tDice.DoThrow(6);

		printf("\n\t   ");
		printf("�ֻ��� . ");
		DisplayGauge(tDice.GetDiceNumber(), 6);
		printf("\n\n");

		if (4 <= tDice.GetDiceNumber())//4�̻� �¸�
		{
			printf("\t");
			printf("����!!!");
			printf("��簡 ������ %d��ŭ ���ظ� ������.", tPlayer->GetPower());
			printf("\n\n");

			DoAttack(tPlayer->GetPower(), tSlime->GetCurrentHealth());
			if (tSlime->GetCurrentHealth() == 0)
			{
				printf("\n\t\t");
				printf("[ �������� ��Ҵ�!! ]");
				printf("\n\n");

				if (tDice.DoThrow(3) <= 3)
				{
					printf("\t\t");
					printf("[ ��簡 ��������. ]");
					printf("\n\n");
					tPlayer->SetHealth(tPlayer->GetHealth() + 2);
					tPlayer->SetPower(tPlayer->GetPower() + 2);
				}
				tResult = 1;
				break;
			}
		}
		else if (3 >= tDice.GetDiceNumber())//3���� �й�
		{
			printf("\t");
			printf("�������� %d��ŭ ���ظ� ������.", tSlime->GetPower());
			printf("\n\n");

			DoAttack(tSlime->GetPower(), tPlayer->GetCurrentHealth());
			if (tPlayer->GetCurrentHealth() == 0)
			{
				break;
			}
		}

	}

	return tResult;
}


void CNormalBattle::DoAttack(int &tPower, int &tTargetHealth)
{
	tTargetHealth -= tPower;
	if (tTargetHealth < 0)
	{
		tTargetHealth = 0;
	}
}


char CBossBattle::DoBattle(CPlayer * tPlayer, CSlime * tSlime)
{
	printf("\n\t\t");
	printf("[ ����,����,�� ���� ]");
	printf("\n\n\t");
	printf("����,����,���� ���� �̱����� �����Ѵ�!");
	printf("\n\n\n");

	while (1)
	{
		printf("[���]");
		DisplayGauge(tPlayer->GetCurrentHealth(), tPlayer->GetHealth());
		printf(" VS ");
		printf("[���� ������]");
		DisplayGauge(tSlime->GetCurrentHealth(), tSlime->GetHealth());
		printf("\n\n");

		printf("[1]:����, [2]:����, [3]:��");
		printf("\n\n");
		printf("�����ϼ��� : ");
		cin >> tPlayerCard;
		printf("\n");
		printf("================================================");
		printf("\n");


		tSlimeDice.DoThrow(3);

		tCompareResult = CheckCompareCard(tPlayerCard, tSlimeDice.GetDiceNumber());

		printf("\n\t\t");
		printf("[���]");
		DisplayCard(tPlayerCard);
		printf(" vs ");
		DisplayCard(tSlimeDice.GetDiceNumber());
		printf("[������]");
		printf("\n\n");


		if (0 == tCompareResult)//���º�
		{
			printf("\t\t\t");
			printf("�����ϴ�.");
			printf("\n\n");

		}
		else if (1 == tCompareResult)//�¸�
		{
			printf("\t");
			printf("�¸�!!");
			printf("��簡 ������ %d��ŭ ���ظ� ������.", tPlayer->GetPower());
			printf("\n\n");

			DoAttack(tPlayer->GetPower(), tSlime->GetCurrentHealth());
			if (tSlime->GetCurrentHealth() == 0)
			{
				printf("\n\t\t");
				printf("[ �������� ��Ҵ�!! ]");
				printf("\n\n");
				tResult = 1;
				break;
			}
		}
		else if (2 == tCompareResult)//�й�
		{
			printf("\t");
			printf("�й�...");
			printf("���� �������� %d��ŭ ���ظ� ������.", tSlime->GetPower());
			printf("\n\n");

			if (tPlayer->GetCurrentHealth() == 0)
			{
				break;
			}
		}

	}

	return tResult;
}

void CBossBattle::DoAttack(int &tPower, int &tTargetHealth)
{
	tTargetHealth -= tPower;
	if (tTargetHealth < 0)
	{
		tTargetHealth = 0;
	}
}