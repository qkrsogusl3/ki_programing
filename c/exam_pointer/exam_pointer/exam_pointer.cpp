// exam_pointer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

//32bit ���α׷��� �޸��ּ��� ũ��� 4byte(=32bit)�̱� ������
//�����ͺ����� ũ��� 4byte
int main()
{
	int *tpA = NULL;
	char *tpC = NULL;

	int tA = 777;
	int tB = 888;

	char tC = 9;

	printf("%d\n", sizeof(tA));
	printf("%d\n", sizeof(tpA));

	printf("%d\n", sizeof(tC));
	printf("%d\n", sizeof(tpC));


	tpA = &tA;

	printf("%d", tpA);
	printf("\n");

	printf("%d", *tpA);
	printf("\n");
	printf("%d", tA);
	printf("\n");

	tpA = &tB;

	printf("%d", tpA);
	printf("\n");

	printf("%d", *tpA);
	printf("\n");
	printf("%d", tA);


	int tInput = 0;
	cin >> tInput;

    return 0;
}

