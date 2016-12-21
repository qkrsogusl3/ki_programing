// exam_5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <stdlib.h>

/*
���� ���߱�

�ϳ��� main.cpp
������ �Լ� �̸� ����
���� �̿�
���ӷ��� ���
��ȸ�� 10��
������ ū�� ������
������ �Լ� �ۼ�



*/
int DoThinkAlphago(int tFrom, int tTo);
int DoCheckInputNumber();
char IsContinue();
void ShowHint(int tPlayer,int tAlphago,int tMaxNumber);


void EvaluateWithRetryCount(int tCount);

int main()
{
	srand(time(NULL));

	int tPlayer = 0;
	int tAlphago = 0;
	char tIsContinue = 'y';

	int tAlphagoMaximumNumber = 10;
	int tPlayerLimitCount = 10;

	int tCurrentCount = 0;

	while ('y' == tIsContinue)
	{
		printf("���� ������ �����մϴ�.\n");
		tCurrentCount = tPlayerLimitCount;
		tAlphago = DoThinkAlphago(0, tAlphagoMaximumNumber);

		while (1)
		{
			printf("���ڸ� �Է��ϼ��� : ");
			tPlayer = DoCheckInputNumber();

			if (tPlayer == tAlphago)
			{
				printf("�����Դϴ�!!\n");
				break;
			}
			else
			{
				//ī��Ʈ ����
				tCurrentCount--;
			
				if (0 < tCurrentCount)
				{
					ShowHint(tPlayer, tAlphago, tAlphagoMaximumNumber);
					EvaluateWithRetryCount(tCurrentCount);
				}
				else
				{
					printf("������ �����Ͽ����ϴ�.\n");
					break;
				}

			}
		}

		tIsContinue = IsContinue();
	}
    return 0;
}

void ShowHint(int tPlayer, int tAlphago, int tMaxNumber)
{
	//��Ʈ
	if (tPlayer > tAlphago)
	{
		printf("���İ��� Ů�ϴ�.\n");
	}
	else if (tPlayer < tAlphago)
	{
		printf("���İ��� �۽��ϴ�.\n");
	}
}


int DoThinkAlphago(int tFrom, int tTo)
{
	int tResult = 0;

	tResult = rand() % (tTo + 1) + tFrom;

	return tResult;
}
int DoCheckInputNumber()
{
	int tInput = 0;

	scanf_s("%d", &tInput);

	return tInput;
}
char IsContinue()
{
	char tInput = 'a';

	while (1)
	{
		printf("��� �ϽǷ���?(y/n)?");
		scanf_s("%c", &tInput);
		scanf_s("%c", &tInput);

		if ('y' == tInput || 'n' == tInput)
		{
			break;
		}
		else
		{
			printf("�Է� ����, y�� n�߿��� �����ϼ���\n");
		}

	}

	return tInput;
}
void EvaluateWithRetryCount(int tCount)
{
	printf("��ȸ�� %d�� ���ҽ��ϴ�.", tCount);
}