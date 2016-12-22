// exam_func_ptr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


int GetNumber();

float DoAddtive(float tA, float tB);
float DoSubtract(float tA, float tB);
float DoMultiply(float tA, float tB);
float DoDivide(float tA, float tB);


//�Լ� ������
int main()
{

	//int *tpA = NULL;

	//int(*tpPtr)() = NULL;
	//int(*tpCalculate)(int, int) = NULL;


	////���ϱ� ������(float)

	//tpPtr = GetNumber;
	//tpCalculate = DoAddtive;
	//

	//int tResult = 0;
	//tResult = tpPtr();
	//printf("%d\n", tResult);

	//tResult = tpCalculate(1, 1);
	//printf("%d\n", tResult);

	//tpCalculate = DoSubtract;
	//tResult = tpCalculate(1, 1);
	//printf("%d\n", tResult);


	/*int tInput = 0;
	std::cin >> tInput;*/

	int tInput = 0;

	float tA = 0;
	float tB = 0;
	float tResult = 0;
	float(*tpCalculate)(float, float) = NULL;

	char tOperater = 0;
	char tIsContinue = 0;

	while (1)
	{

		printf("0.���ϱ�\n1.����\n2.���ϱ�\n3.������\n");
		std::cin >> tInput;

		printf("ù��° ���ڸ� �Է��ϼ��� : ");
		std::cin >> tA;
		printf("�ι�° ���ڸ� �Է��ϼ��� : ");
		std::cin >> tB;
		printf("\n");


		switch (tInput)
		{
		case 0://���ϱ�
			tOperater = '+';
			tpCalculate = DoAddtive;
			break;
		case 1://����
			tOperater = '-';
			tpCalculate = DoSubtract;
			break;
		case 2://���ϱ�
			tOperater = '*';
			tpCalculate = DoMultiply;
			break;
		case 3://������
			tOperater = '/';
			tpCalculate = DoDivide;
			break;
		}

		if (tpCalculate != NULL)
		{
			tResult = tpCalculate(tA, tB);
			printf("��� : %f %c %f = %f\n", tA, tOperater, tB, tResult);
		}

		printf("�����Ͻðڽ��ϱ�?(y/n) : ");
		std::cin >> tIsContinue;

		if (tIsContinue != 'n')
		{
			break;
		}
	}


	return 0;
}

int GetNumber()
{
	return 777;
}


float DoAddtive(float tA, float tB)
{
	return tA + tB;
}
float DoSubtract(float tA, float tB)
{
	return tA - tB;
}

float DoMultiply(float tA, float tB)
{
	return tA * tB;
}
float DoDivide(float tA, float tB)
{
	return tA / tB;
}
