// 1d_game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <stdlib.h>
#include <time.h>

#define YES 'y'
#define NO 'n'

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

int DisplayTitle();
void PlayerToMove(Player *tPlayer, int tMap[],int tIndex);
void DrawMap(int tMap[]);
char CheckSlimeEncount(Player *tPlayer, int tMap[]);

void DoAttack(int tPower, int *tTargetCurrentHealth);

char DoNormalBattle(Player *tPlayer, Slime *tSlime);
int DoThrowDice(int tMaxNumber);

char DoBossBattle(Player *tPlayer, Slime *tSlime);
char CheckCompareCard(int tPlayerCard, int tSlimeCard);
void DisplayCard(int tCardValue);

void DisplayGauge(int tCurrentValue, int tMaxValue);


int main()
{
	
	srand(time(NULL));

	int tGameState = TITLE;//���ӽ��� �� Ÿ��Ʋ ����
	int tMap[MAP_LENGTH] = { 0 };//������ �ʱ��̷� ��ҵ� �ʱ�ȭ
	int tInput = 0;//Input�Է� �޴� ����
	char tIsContinue = YES;

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


	while (NO != tIsContinue)
	{
		switch (tGameState)
		{
		case TITLE://Ÿ��Ʋ
			tGameState = DisplayTitle();
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

			if (CheckSlimeEncount(tPlayer, tMap))//���� ����ħ
			{
				int tSlimeKind = 0;
				Slime *tSlime = NULL;

				//���� �÷��̾� ��ġ+1�� ���ֺ��� ������ ����
				tSlimeKind = tMap[tPlayer->mPosition + 1];

				if (tSlimeKind == KIND_NORMAL_SLIME)
				{
					printf("\t[ �Ϲ� �������� ��Ÿ����. ]\n\n");
					tSlime = tNormalSlime;
				}
				else if (tSlimeKind == KIND_BOSS_SLIME)
				{
					printf("\t[ ���� �������� ��Ÿ����. ]\n\n");
					tSlime = tBossSlime;
				}

				printf("1.�ο��� �Ǵ�!!\n2.����ģ��..\n");
				cin >> tInput;

				if (tInput == 1)
				{
					int tBattleResult = 0;
					//printf("\t[ ������ �����ߴ�!! ]\n\n");
					tBattleResult = tSlime->mDoBattle(tPlayer, tSlime);

					if (tBattleResult == 1)//�¸�
					{
						//��� ü�� ȸ��
						tPlayer->mCurrentHealth = tPlayer->mHealth;

						//�������� �ִ� ��ġ �ʱ�ȭ
						tMap[tPlayer->mPosition + 1] = 0;
						//���� ��ġ�� �̵�
						PlayerToMove(tPlayer, tMap, tPlayer->mPosition + 1);
					}
					else if (tBattleResult == 0)//�й�
					{
						printf("\n\n\t\t[ ���� �׾���... ]\n\n\n");
						
						tGameState = QUIT;
					}

					printf("Input Any Key\n");
					cin >> tInput;
				}
				else if (tInput == 2)
				{
					printf("\t[ ���� �����ƴ�... ]\n");
					PlayerToMove(tPlayer, tMap, tPlayer->mPosition - 1);
				}
			}
			else//���� ����ġ�� ����
			{
				if (tPlayer->mPosition != MAP_LENGTH - 1)//�� ���� �������� �ʾ�����
				{
					printf("\t[ ��� �ұ�? ]\n\n");
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
					printf("\t[ ������ Ŭ�����Ͽ����ϴ�. ]\n\n");
					printf("Input Any Key\n");
					cin >> tInput;
					tGameState = QUIT;
				}
			}

			break;
		case QUIT://����
			printf("\n\n\n����Ͻðڽ��ϱ�?(y/n): ");
			cin >> tIsContinue;
			if (YES == tIsContinue)
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

int DisplayTitle()
{
	int tInput = 0;


	printf("\n\n\t[ ���� ������ ]\n\n\n");
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

		printf("\t[ �̵� �� �� ����... ]\n");
		printf("Input Any Key\n");
		cin >> tInput;
	}

}

void DrawMap(int tMap[])
{
	int ti = 0;

	printf("====================================");
	printf("====================================");
	printf("\n==");
	for (ti = 0; ti < MAP_LENGTH; ti++)
	{
		switch (tMap[ti])
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

	printf("\t\t[�ֻ��� ��Ʋ]\n");
	printf("\t������ 4�̻��̸� ��簡 ����!\n");
	printf("\t������ 3���ϸ� �������� �����Ѵ�.\n\n");

	while (1)
	{
		printf("\t[���]");
		DisplayGauge(tPlayer->mCurrentHealth, tPlayer->mHealth);
		printf(" VS ");
		printf("[������]");
		DisplayGauge(tSlime->mCurrentHealth, tSlime->mHealth);
		printf("\n\n");

		printf("1. �ֻ����� ������.\n");
		cin >> tInput;

		printf("================================================\n\n");
		tDiceNumber = DoThrowDice(6);

		printf("\n\t   �ֻ��� -> ");
		DisplayGauge(tDiceNumber, 6);
		printf("\n\n");

		if (4 <= tDiceNumber)//4�̻� �¸�
		{
			printf("\t����!!!");
			printf("��簡 ������ %d��ŭ ���ظ� ������.\n\n", tPlayer->mPower);
			DoAttack(tPlayer->mPower,&tSlime->mCurrentHealth);
			if (tSlime->mCurrentHealth == 0)
			{
				printf("\n\t\t[ �������� ��Ҵ�!! ]\n\n");

				if (DoThrowDice(3) <= 3)
				{
					printf("\t\t[ ��簡 ��������. ]\n\n");
					tPlayer->mHealth += 2;
					tPlayer->mPower += 2;
				}
				tResult = 1;
				break;
			}
		}
		else if (3 >= tDiceNumber)//3���� �й�
		{
			printf("\t�������� %d��ŭ ���ظ� ������.\n\n", tSlime->mPower);
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

	printf("\n\t\t[ ����,����,�� ���� ]\n\n");
	printf("\t����,����,���� ���� �̱����� �����Ѵ�!\n\n\n");

	while (1)
	{
		printf("[���]");
		DisplayGauge(tPlayer->mCurrentHealth, tPlayer->mHealth);
		printf(" VS ");
		printf("[���� ������]");
		DisplayGauge(tSlime->mCurrentHealth, tSlime->mHealth);
		printf("\n\n");

		printf("[1]:����, [2]:����, [3]:��\n\n");
		printf("�����ϼ��� : ");
		cin >> tPlayerCard;
		printf("\n================================================\n");


		tSlimeCard = DoThrowDice(3);

		tCompareResult = CheckCompareCard(tPlayerCard, tSlimeCard);

		printf("\n\t\t");
		printf("[���]");
		DisplayCard(tPlayerCard);
		printf(" vs ");
		DisplayCard(tSlimeCard);
		printf("[������]");
		printf("\n\n");

		
		if (0 == tCompareResult)//���º�
		{
			printf("\t\t\t�����ϴ�.\n\n");
		}
		else if (1 == tCompareResult)//�¸�
		{
			printf("\t�¸�!!");
			printf("��簡 ������ %d��ŭ ���ظ� ������.\n\n", tPlayer->mPower);
			DoAttack(tPlayer->mPower, &tSlime->mCurrentHealth);
			if (tSlime->mCurrentHealth == 0)
			{
				printf("\n\t\t[ �������� ��Ҵ�!! ]\n\n");
				tResult = 1;
				break;
			}
		}
		else if (2 == tCompareResult)//�й�
		{
			printf("\t�й�...");
			printf("���� �������� %d��ŭ ���ظ� ������.\n\n", tSlime->mPower);
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
