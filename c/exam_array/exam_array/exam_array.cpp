// exam_array.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

//������ �ε����� �Ű������� �޾Ƽ� �� �ε����� �ش��ϴ� ���� ���� �ٲٴ� �Լ�
void DoChangeElementWith(int tArray[],int tIndex,int tValue);

int main()
{

	int tArray[5] = { 0,0,0,0,0 };

	tArray[0] = 4;
	tArray[1] = 0;
	tArray[2] = 1;
	tArray[3] = 2;
	tArray[4] = 3;

	int ti = 0;

	for (ti = 0; ti < 5; ti++)
	{
		printf("%d\n", tArray[ti]);
	}


	//�迭�� �̸��� ���ӵ� �޸� ���� ���� �ּ�
	//tArray == &tArray[0]
	printf("%d\n", tArray);
	printf("%d\n", &tArray[0]);


	//[0]�޸� ��ġ���� 5��° ��ġ�� �޸� �ּ�
	//[0]�ּ� + (integer size * 5) = [5]�� �ּ�
	printf("%d\n", &tArray[5]);
	printf("%d\n", &tArray[6]);


	//[0]�޸� ��ġ���� 5��° ��ġ�� �޸𸮿� �ʱ�ȭ ���� ���� ��(�����Ⱚ)
	//����� �����Ѵٴ°� ������ ������ �޸� ���� ������ �Ҵ�޾� �ʱ�ȭ�Ѵٴ� ��
	printf("%d\n", tArray[5]);
	printf("%d\n", tArray[6]);


	DoChangeElementWith(tArray, 0, 100);
	printf("%d\n", tArray[0]);


	int tInput = 0;
	cin >> tInput;


    return 0;
}

void DoChangeElementWith(int tArray[], int tIndex, int tValue)
{
	tArray[tIndex] = tValue;
}


