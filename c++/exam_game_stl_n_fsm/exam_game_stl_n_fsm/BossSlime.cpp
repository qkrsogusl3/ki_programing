#include "stdafx.h"
#include "BossSlime.h"
#include "Dice.h"
#include <iostream>

using namespace std;

CBossSlie::CBossSlie()
{
}


CBossSlie::~CBossSlie()
{
}

char CBossSlie::DoBattle(CPlayer * tPlayer)
{
	int tPlayerCard = 0;
	int tCompareResult = 0;

	char tResult = 0;
	CDice tSlimeDice;

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
		DisplayGauge(mCurrentHealth, mHealth);
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

			tPlayer->DoAttack(this);
			if (mCurrentHealth == 0)
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
			printf("���� �������� %d��ŭ ���ظ� ������.", mPower);
			printf("\n\n");

			DoAttack(tPlayer);
			if (tPlayer->GetCurrentHealth() == 0)
			{
				break;
			}
		}

	}

	return tResult;

}

char CBossSlie::CheckCompareCard(int tPlayerCard, int tSlimeCard)
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

void CBossSlie::DisplayCard(int tCardValue)
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
