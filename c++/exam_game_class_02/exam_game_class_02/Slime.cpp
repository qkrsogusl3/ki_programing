#include "stdafx.h"
#include "Slime.h"
#include "Dice.h"

#include <iostream>
using namespace std;

CSlime::CSlime()
{
}


CSlime::~CSlime()
{
}

//todo : DisplayGuage
char CSlime::DoBattle(CPlayer * tPlayer)
{
	int tInput = 0;
	char tResult = 0;

	CDice tDice;

	while (1)
	{
		printf("\t");
		printf("[���]");
		DisplayGauge(tPlayer->GetCurrentHealth(), tPlayer->GetHealth());
		printf(" VS ");
		printf("[������]");
		DisplayGauge(mCurrentHealth, mHealth);
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

			tPlayer->DoAttack(this);
			if (this->GetCurrentHealth() == 0)
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
			printf("�������� %d��ŭ ���ظ� ������.", this->GetPower());
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
