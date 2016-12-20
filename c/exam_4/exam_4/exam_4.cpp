// exam_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
/*
����������

�ϳ��� main.cpp
������ �Լ��̸� ����
���� �̿�
�������Ǻ� switch
�Լ� �̿�

���� 0
���� 1
�� 2

*/

int DoAlphaGoAction();
int CheckWinner(int tPlayer, int tAlphaGo);
void ShowAction(int tAction);

int main()
{
	srand(time(NULL));
	
	int tPlayer = 0;
	int tAlphaGo = 0;
	int tWinner = 0;

	while (1)
	{
		printf("1. Play\n2. Exit\n");

		scanf_s("%d", &tPlayer);

		if (1 == tPlayer)
		{
			do
			{
				printf("����,����,���� ������ �ּ���.\n");
				printf("0:����\t1:����\t��:2\n");
				scanf_s("%d", &tPlayer);

			} while (0 > tPlayer || 3 <= tPlayer);//����,����,�� �ܴ̿� ���Է�


			tAlphaGo = DoAlphaGoAction();


			printf("===�÷��̾�===\n");
			ShowAction(tPlayer);
			printf("===���İ�===\n");
			ShowAction(tAlphaGo);


			tWinner = CheckWinner(tPlayer, tAlphaGo);

			switch (tWinner)
			{
			case 0:
				printf("\n�����ϴ�.\n");
				break;
			case 1:
				printf("\n�̰���ϴ�.\n");
				break;
			case 2:
				printf("\n�����ϴ�.\n");
				break;
			}

		
		}
		else if (2 == tPlayer)
		{
			break;
		}

	}

    return 0;
}


int DoAlphaGoAction()
{
	int tResult = 0;

	tResult = rand() % 3 + 0;

	return tResult;
}

//����,����,�� �ؽ�Ʈ ���
void ShowAction(int tAction)
{
	switch (tAction)
	{
	case 0:
		printf("����\n");
		break;
	case 1:
		printf("����\n");
		break;
	case 2:
		printf("��\n");
		break;
	}
}


/*
���� ����

Return:
	1 Player Win
	0 Draw
	-1 AlphaGo Win
*/
int CheckWinner(int tPlayer, int tAlphaGo) 
{
	int tWinner = 0;

	int tResult = tPlayer - tAlphaGo;

	switch (tResult)
	{
	case 0:
		tWinner = 0;
		break;
	case 1:
		tWinner = 1;
		break;
	case -2:
		tWinner = 1;
		break;
	case -1:
		tWinner = -1;
		break;
	case 2:
		tWinner = -1;
		break;
	}
	
	return tWinner;
}

