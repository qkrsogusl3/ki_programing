// 1d_game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <stdlib.h>
#include <time.h>

//State Values
#define TITLE 0
#define PLAY 1
#define QUIT 2
#define INIT 3

//Player,Monsters Kind
#define KIND_PLAYER 11
#define KIND_NORMAL_SLIME 12
#define KIND_BOSS_SLIME 13

#define MAP_LENGTH 5
#define MAX_HEALTH 10

using namespace std;

struct Player
{
	int mHealth = 0;
	int mCurrentHealth = 0;
	int mPower = 0;

	int mPosition = 0;
};

struct Slime
{
	int mHealth = 0;
	int mCurrentHealth = 0;
	int mPower = 0;

	char(*mDoBattle)(Player *tPlayer,Slime *tSlime) = NULL;
};

int DrawTitle();
void PlayerToMove(Player *tPlayer, int tMap[],int tIndex);
void DrawMap(int tMap[]);
char CheckSlimeEncount(Player *tPlayer, int tMap[]);

void DoAttack(int tPower, int *tTargetCurrentHealth);

char DoNormalBattle(Player *tPlayer, Slime *tSlime);
int DoThrowDice(int tMaxNumber);

char DoBossBattle(Player *tPlayer, Slime *tSlime);
char CheckCompareCard(int tPlayerCard, int tSlimeCard);
void DisplayCard(int tCardValue);

void DisplayHealth(int tHealth, int tCurrentHealth);


int main()
{
	srand(time(NULL));

	int tGameState = TITLE;//���ӽ��� �� Ÿ��Ʋ ����
	int tMap[MAP_LENGTH] = { 0 };//������ �ʱ��̷� ��ҵ� �ʱ�ȭ
	int tInput = 0;//Input�Է� �޴� ����
	char tIsContinue = 'y';

	Player *tPlayer = NULL;
	Slime *tNormalSlime = NULL;
	Slime *tBossSlime = NULL;

	tPlayer = new Player();
	tNormalSlime = new Slime();
	tBossSlime = new Slime();

	tPlayer->mHealth = 5;

	tNormalSlime->mHealth = 5;
	tNormalSlime->mDoBattle = DoNormalBattle;//�ֻ��� ����

	tBossSlime->mHealth = 10;
	tBossSlime->mDoBattle = DoBossBattle;//����,����,��

	

	while ('n' != tIsContinue)
	{
		switch (tGameState)
		{
		case TITLE://Ÿ��Ʋ
			tGameState = DrawTitle();
			break;
		case INIT://����� �� �ʱ�ȭ ��
			tPlayer->mCurrentHealth = tPlayer->mHealth;
			tPlayer->mPower = 1;

			tNormalSlime->mCurrentHealth = tNormalSlime->mHealth;
			tNormalSlime->mPower = 1;

			tBossSlime->mCurrentHealth = tBossSlime->mHealth;
			tBossSlime->mPower = 2;

			
			//�÷��̾� �ʱ���ġ�� �̵�
			PlayerToMove(tPlayer, tMap, 0);
			//2������ �Ϲ� �������� �ִ�. 
			tMap[2] = KIND_NORMAL_SLIME;
			//4������ ���� �������� �ִ�.
			tMap[4] = KIND_BOSS_SLIME;


			tGameState = PLAY;
			break;
		case PLAY:
			DrawMap(tMap);

			if (CheckSlimeEncount(tPlayer, tMap))//Encount
			{
				int tSlimeKind = 0;
				Slime *tSlime = NULL;

				//���� �÷��̾� ��ġ+1�� ���ֺ��� ������ ����
				tSlimeKind = tMap[tPlayer->mPosition + 1];

				if (tSlimeKind == KIND_NORMAL_SLIME)
				{
					printf("�߻��� �Ϲ� �������� ��Ÿ����.\n");
					tSlime = tNormalSlime;
				}
				else if (tSlimeKind == KIND_BOSS_SLIME)
				{
					printf("�߻��� ���� �������� ��Ÿ����.\n");
					tSlime = tBossSlime;
				}

				printf("1.�ο��� �Ǵ�!!\n2.����ģ��..\n");
				cin >> tInput;

				if (tInput == 1)
				{
					int tBattleResult = 0;
					printf("������ �����ߴ�!!\n");
					tBattleResult = tSlime->mDoBattle(tPlayer, tSlime);

					if (tBattleResult == 1)//�¸�
					{
						//�������� �ִ� ��ġ �ʱ�ȭ
						tMap[tPlayer->mPosition + 1] = 0;
						//���� ��ġ�� �̵�
						PlayerToMove(tPlayer, tMap, tPlayer->mPosition + 1);
					}
					else if (tBattleResult == 0)//�й�
					{
						printf("���� �׾���...\n\n\n");
						
						tGameState = QUIT;
					}

					printf("Input Any Key\n\n\n");
					cin >> tInput;
				}
				else if (tInput == 2)
				{
					printf("���� �����ƴ�...\n");
					PlayerToMove(tPlayer, tMap, tPlayer->mPosition - 1);
				}
			}
			else
			{
				if (tPlayer->mPosition != MAP_LENGTH - 1)//�� ���� �������� �ʾ�����
				{
					printf("��� �ұ�?\n");
					printf("1.�����ϱ�\n2.���ư���\n");
					cin >> tInput;

					if (tInput == 1)
					{
						PlayerToMove(tPlayer, tMap, tPlayer->mPosition + 1);
					}
					else if (tInput == 2)
					{
						PlayerToMove(tPlayer, tMap, tPlayer->mPosition - 1);
					}
				}
				else
				{
					printf("������ Ŭ�����Ͽ����ϴ�.\n");
					printf("Input Any Key\n");
					cin >> tInput;
					tGameState = QUIT;
				}
			}

			break;
		case QUIT://����
			printf("����Ͻðڽ��ϱ�?(y/n): ");
			cin >> tIsContinue;
			if ('y' == tIsContinue)
			{
				tGameState = 0;
			}
			break;
		}
		system("cls");
	}

	if (tPlayer != NULL)
	{
		delete tPlayer;
		tPlayer = NULL;
	}
	if (tNormalSlime != NULL)
	{
		delete tNormalSlime;
		tNormalSlime = NULL;
	}
	if (tBossSlime != NULL)
	{
		delete tBossSlime;
		tBossSlime = NULL;
	}

	return 0;
}

int DrawTitle()
{
	int tInput = 0;

	printf("���� ������\n\n");
	printf("1.���� ����\n");
	printf("2.����\n");

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

void PlayerToMove(Player *tPlayer, int tMap[], int tIndex)
{
	if (tIndex >= 0 && tIndex < MAP_LENGTH)
	{
		tMap[tPlayer->mPosition] = 0;
		tMap[tIndex] = KIND_PLAYER;
		tPlayer->mPosition = tIndex;
	}
	else
	{
		int tInput = 0;

		printf("�̵� �� �� ����....\n");
		printf("[Input Any Key] ���\n");
		cin >> tInput;
	}

}

void DrawMap(int tMap[])
{
	int ti = 0;

	printf("==========================================");
	printf("=========================================");
	printf("\n==");
	for (ti = 0; ti < MAP_LENGTH; ti++)
	{
		switch (tMap[ti])
		{
		case KIND_PLAYER:
			printf("[   PLAYER   ]==");
			break;
		case KIND_NORMAL_SLIME:
			printf("[    SLIME   ]==");
			break;
		case KIND_BOSS_SLIME:
			printf("[ BOSS SLIME ]==");
			break;
		case 0://����
		default:
			printf("[            ]==");
			break;
		}
	}
	printf("\n");
	printf("==========================================");
	printf("=========================================");
	printf("\n\n");

}
char CheckSlimeEncount(Player *tPlayer, int tMap[])
{
	char tResult = 0;

	if (tPlayer != NULL && tPlayer->mPosition < MAP_LENGTH - 1)
	{
		if (tMap[tPlayer->mPosition + 1] != 0)
		{
			tResult = 1;
		}
	}
	return tResult;
}

void DoAttack(int tPower, int *tTargetCurrentHealth) 
{
	*tTargetCurrentHealth -= tPower;
	if (*tTargetCurrentHealth < 0)
	{
		*tTargetCurrentHealth = 0;
	}
}

char DoNormalBattle(Player *tPlayer, Slime *tSlime)
{
	int tInput = 0;
	int tDiceNumber = 0;

	char tResult = 0;

	printf("�ֻ��� ��Ʋ\n\n");
	printf("������ 4�̻��̸� ��簡 ����!\n");
	printf("������ 3���ϸ� �������� �����Ѵ�.\n");

	while (1)
	{
		printf("[���]");
		DisplayHealth(tPlayer->mHealth, tPlayer->mCurrentHealth);
		printf(" VS ");
		printf("[������]");
		DisplayHealth(tSlime->mHealth, tSlime->mCurrentHealth);
		printf("\n\n");

		printf("1. �ֻ����� ������.\n");
		cin >> tInput;

		//tDiceNumber = DoThrowDice(6);
		tDiceNumber = 4;

		printf("���� : %d\n", tDiceNumber);

		if (4 <= tDiceNumber)//4�̻� �¸�
		{
			printf("����!!! ");
			printf("��簡 ������ %d��ŭ ���ظ� ������.\n", tPlayer->mPower);
			DoAttack(tPlayer->mPower,&tSlime->mCurrentHealth);
			if (tSlime->mCurrentHealth == 0)
			{
				printf("�������� ��Ҵ�!!\n");

				if (DoThrowDice(3) <= 1)
				{
					printf("��簡 ��������.\n");
					tPlayer->mPower += 2;
				}
				tResult = 1;
				break;
			}
		}
		else if (3 >= tDiceNumber)//3���� �й�
		{
			printf("�������� %d��ŭ ���ظ� ������.\n", tSlime->mPower);
			DoAttack(tSlime->mPower, &tPlayer->mCurrentHealth);
			if (tPlayer->mCurrentHealth == 0)
			{
				break;
			}
		}
	}

	return tResult;
}
int DoThrowDice(int tMaxNumber)
{
	int tResult = 0;

	tResult = rand() % tMaxNumber + 1;
	//tResult = 4;

	return tResult;
}


char DoBossBattle(Player *tPlayer, Slime *tSlime)
{
	int tPlayerCard = 0;
	int tSlimeCard = 0;
	int tCompareResult = 0;

	char tResult = 0;

	printf("����,����,�� ����\n\n");
	printf("����,����,���� ���� �̱����� �����Ѵ�!\n\n");

	while (1)
	{
		printf("[���]");
		DisplayHealth(tPlayer->mHealth, tPlayer->mCurrentHealth);
		printf(" VS ");
		printf("[���� ������]");
		DisplayHealth(tSlime->mHealth, tSlime->mCurrentHealth);
		printf("\n\n");

		printf("[1]:����, [2]:����, [3]:��\n");
		printf("�����ϼ��� : ");
		cin >> tPlayerCard;

		tSlimeCard = DoThrowDice(3);

		tCompareResult = CheckCompareCard(tPlayerCard, tSlimeCard);

		printf("\n");
		printf("[���]");
		DisplayCard(tPlayerCard);
		printf(" vs ");
		DisplayCard(tSlimeCard);
		printf("[������]");
		printf("\n");

		if (0 == tCompareResult)//���º�
		{
			printf("�����ϴ�.\n");
		}
		else if (1 == tCompareResult)//�¸�
		{
			printf("�¸�!!! ");
			printf("��簡 ������ %d��ŭ ���ظ� ������.\n", tPlayer->mPower);
			DoAttack(tPlayer->mPower, &tSlime->mCurrentHealth);
			if (tSlime->mCurrentHealth == 0)
			{
				printf("���� �������� ��Ҵ�!!\n");
				tResult = 1;
				break;
			}
		}
		else if (2 == tCompareResult)//�й�
		{
			printf("�й�... ");
			printf("���� �������� %d��ŭ ���ظ� ������.\n", tSlime->mPower);
			DoAttack(tSlime->mPower, &tPlayer->mCurrentHealth);
			if (tPlayer->mCurrentHealth == 0)
			{
				break;
			}
		}

	}

	return tResult;
}

char CheckCompareCard(int tPlayerCard, int tSlimeCard)
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
void DisplayCard(int tCardValue)
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


void DisplayHealth(int tHealth, int tCurrentHealth)
{
	int ti = 0;

	for (ti = 0; ti < tCurrentHealth; ti++)
	{
		printf("��");
	}
	for (ti = 0; ti < tHealth - tCurrentHealth; ti++)
	{
		printf("��");
	}  

}
