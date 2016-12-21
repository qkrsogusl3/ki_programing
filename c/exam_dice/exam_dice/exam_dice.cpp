// exam_dice.cpp : Defines the entry point for the console application.
//

//����� ���� ��� ����
#include "stdafx.h"

//ǥ�� ��� ����
#include <stdlib.h>
#include <time.h>

int DoRollDice(int tMin,int tMax);
void ShowDiceResult(int tDiceNumber);

int main()
{
	srand(time(NULL));

	int tDiceNumber = 0;
	int tDiceSide = 0;
	int tIsContinue = 0;

	printf("�ֻ����� ���� ���� : ");
	scanf_s("%d", &tDiceSide);

	while (1)
	{

		/*printf("�ֻ����� ���� ����(0:����) : ");
		scanf_s("%d", &tDiceSide);
		
		if (0 == tDiceSide)
		{
			break;
		}*/

		printf("�ֻ����� �������?(1/0)\t");
		scanf_s("%d", &tIsContinue);


		if (0 == tIsContinue)
		{
			break;
		}
		
		
		tDiceNumber = DoRollDice(1, tDiceSide);

		printf("%d", tDiceNumber);
		printf("\n");

		ShowDiceResult(tDiceNumber);

	}


    return 0;
}

void ShowDiceResult(int tDiceNumber)
{
	//�Լ��� ���� �۵��ϰ� ���弼��
	switch (tDiceNumber)
	{
	case 1:
	case 2:
	case 3:
		printf("you lose\n");
		break;
	default:
		printf("you win\n");
		break;
	}

	//�Ǵ�, 3���� ��,4�̻� ��
	/*
	if (tDiceNumber <= 3)
	{
	printf("you lose\n");
	}
	else// if(tDiceNumber >= 4)
	{
	printf("you win\n");
	}
	*/

}


int DoRollDice(int tMin, int tMax)
{
	int tResult = 0;

	tResult = rand() % tMax + tMin;

	return tResult;
}

