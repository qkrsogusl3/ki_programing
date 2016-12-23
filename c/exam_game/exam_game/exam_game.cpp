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
	
	srand(time(NULL));//���� �õ� ����

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


	tNormalSlime->mDoBattle = DoNormalBattle;//�ֻ��� ����

	tBossSlime->mDoBattle = DoBossBattle;//����,����,��


	while (NO != tIsContinue)
	{
		switch (tGameState)
		{
		case TITLE://Ÿ��Ʋ
			tGameState = DisplayTitle();
			break;
		case INIT://����� �� �ʱ�ȭ ��
			tPlayer->mHealth = 5;
			tPlayer->mCurrentHealth = tPlayer->mHealth;
			tPlayer->mPower = 1;

			tNormalSlime->mHealth = 5;
			tNormalSlime->mCurrentHealth = tNormalSlime->mHealth;
			tNormalSlime->mPower = 1;

			tBossSlime->mHealth = 10;
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
					printf("\t");
					printf("[ �Ϲ� �������� ��Ÿ����. ]");
					printf("\n\n");
					tSlime = tNormalSlime;
				}
				else if (tSlimeKind == KIND_BOSS_SLIME)
				{
					printf("\t");
					printf("[ ���� �������� ��Ÿ����. ]");
					printf("\n\n");
					tSlime = tBossSlime;
				}

				printf("1.�ο��� �Ǵ�!!");
				printf("\n");
				printf("2.����ģ��..");
				printf("\n");
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
						printf("\n\n\t\t");
						printf("[ ���� �׾���... ]");
						printf("\n\n\n");

						tGameState = QUIT;
					}

					printf("Input Any Key");
					printf("\n");
					cin >> tInput;
				}
				else if (tInput == 2)
				{
					printf("\t");
					printf("[ ���� �����ƴ�... ]");
					printf("\n");

					PlayerToMove(tPlayer, tMap, tPlayer->mPosition - 1);
				}
			}
			else//���� ����ġ�� ����
			{
				if (tPlayer->mPosition != MAP_LENGTH - 1)//�� ���� �������� �ʾ�����
				{
					printf("\t");
					printf("[ ��� �ұ�? ]");
					printf("\n\n");
					printf("1.�����ϱ�");
					printf("\n");
					printf("2.���ư���");
					printf("\n");


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
					printf("\t");
					printf("[ ������ Ŭ�����Ͽ����ϴ�. ]");
					printf("\n\n");
					printf("Input Any Key");
					printf("\n");

					cin >> tInput;
					tGameState = QUIT;
				}
			}

			break;
		case QUIT://����
			printf("\n\n\n");
			printf("����Ͻðڽ��ϱ�?(y/n): ");
			cin >> tIsContinue;
			if (YES == tIsContinue)
			{
				tGameState = 0;
			}
			break;
		}
		system("cls");
	}

	//�� �����Ҵ� ������ �ʱ�ȭ
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

//Ÿ��Ʋ ȭ���� �׸��� 
//����,���Ḧ �Է¹޴´�.
int DisplayTitle()
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

		printf("\t");
		printf("[ �̵� �� �� ����... ]");
		printf("\n");
		printf("Input Any Key");
		printf("\n");
		cin >> tInput;
	}

}

//������ �� ���¸� �׸���.
void DrawMap(int tMap[])
{
	int ti = 0;

	printf("====================================");
	printf("====================================");
	printf("\n");
	printf("==");
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

//�÷��̾ ���� ���ֺ��� �ִ��� �˻��Ѵ�.
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

//Power������ ����� Health���� ���� ��Ų��
//���� ������ -1���ϴ� 0���� ������Ų��
void DoAttack(int tPower, int *tTargetCurrentHealth) 
{
	*tTargetCurrentHealth -= tPower;
	if (*tTargetCurrentHealth < 0)
	{
		*tTargetCurrentHealth = 0;
	}
}

//�Ϲ� �������� ���� ���
//�ֻ��� ����
char DoNormalBattle(Player *tPlayer, Slime *tSlime)
{
	int tInput = 0;
	int tDiceNumber = 0;

	char tResult = 0;

	printf("\t\t");
	printf("[�ֻ��� ��Ʋ]");
	printf("\n\t");
	printf("������ 4�̻��̸� ��簡 ����!");
	printf("\n\t");
	printf("������ 3���ϸ� �������� �����Ѵ�.");
	printf("\n\n");

	while (1)
	{
		printf("\t");
		printf("[���]");
		DisplayGauge(tPlayer->mCurrentHealth, tPlayer->mHealth);
		printf(" VS ");
		printf("[������]");
		DisplayGauge(tSlime->mCurrentHealth, tSlime->mHealth);
		printf("\n\n");

		printf("1. �ֻ����� ������.");
		printf("\n");
		cin >> tInput;

		printf("================================================");
		printf("\n\n");
		tDiceNumber = DoThrowDice(6);

		tDiceNumber = 4;//�׽�Ʈ

		printf("\n\t   ");
		printf("�ֻ��� -> ");
		DisplayGauge(tDiceNumber, 6);
		printf("\n\n");

		if (4 <= tDiceNumber)//4�̻� �¸�
		{
			printf("\t");
			printf("����!!!");
			printf("��簡 ������ %d��ŭ ���ظ� ������.", tPlayer->mPower);
			printf("\n\n");

			DoAttack(tPlayer->mPower,&tSlime->mCurrentHealth);
			if (tSlime->mCurrentHealth == 0)
			{
				printf("\n\t\t");
				printf("[ �������� ��Ҵ�!! ]");
				printf("\n\n");

				if (DoThrowDice(3) <= 3)
				{
					printf("\t\t");
					printf("[ ��簡 ��������. ]");
					printf("\n\n");
					tPlayer->mHealth += 2;
					tPlayer->mPower += 2;
				}
				tResult = 1;
				break;
			}
		}
		else if (3 >= tDiceNumber)//3���� �й�
		{
			printf("\t");
			printf("�������� %d��ŭ ���ظ� ������.", tSlime->mPower);
			printf("\n\n");

			DoAttack(tSlime->mPower, &tPlayer->mCurrentHealth);
			if (tPlayer->mCurrentHealth == 0)
			{
				break;
			}
		}

	}

	return tResult;
}

//�ֻ����� ���� ������ �����Ѵ�.
int DoThrowDice(int tMaxNumber)
{
	int tResult = 0;

	tResult = rand() % tMaxNumber + 1;

	return tResult;
}

//������������ ���� ���
//����,����,��
char DoBossBattle(Player *tPlayer, Slime *tSlime)
{
	int tPlayerCard = 0;
	int tSlimeCard = 0;
	int tCompareResult = 0;

	char tResult = 0;

	printf("\n\t\t");
	printf("[ ����,����,�� ���� ]");
	printf("\n\n\t");
	printf("����,����,���� ���� �̱����� �����Ѵ�!");
	printf("\n\n\n");

	while (1)
	{
		printf("[���]");
		DisplayGauge(tPlayer->mCurrentHealth, tPlayer->mHealth);
		printf(" VS ");
		printf("[���� ������]");
		DisplayGauge(tSlime->mCurrentHealth, tSlime->mHealth);
		printf("\n\n");

		printf("[1]:����, [2]:����, [3]:��");
		printf("\n\n");
		printf("�����ϼ��� : ");
		cin >> tPlayerCard;
		printf("\n");
		printf("================================================");
		printf("\n");


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
			printf("\t\t\t");
			printf("�����ϴ�.");
			printf("\n\n");

		}
		else if (1 == tCompareResult)//�¸�
		{
			printf("\t");
			printf("�¸�!!");
			printf("��簡 ������ %d��ŭ ���ظ� ������.", tPlayer->mPower);
			printf("\n\n");

			DoAttack(tPlayer->mPower, &tSlime->mCurrentHealth);
			if (tSlime->mCurrentHealth == 0)
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
			printf("���� �������� %d��ŭ ���ظ� ������.", tSlime->mPower);
			printf("\n\n");

			DoAttack(tSlime->mPower, &tPlayer->mCurrentHealth);
			if (tPlayer->mCurrentHealth == 0)
			{
				break;
			}
		}

	}

	return tResult;
}

//�÷��̾�� �������� �и� ���Ͽ� ����� �����Ѵ�.
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
//�� ���� �´� �ؽ�Ʈ�� ����Ѵ�.
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
