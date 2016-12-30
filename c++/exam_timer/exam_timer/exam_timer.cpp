// exam_timer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <Windows.h>
#include <WinBase.h>

using namespace std;

#define DELAY_INTERVAL 1000

void OnTimeDoSomething();

int main()
{

	void(*tpPtr)() = NULL;
	tpPtr = OnTimeDoSomething;


	int tDelay = 0;
	int tTemp = 0;

	int tCount = 0;

	while (true)
	{
		if (0 == tDelay)
		{
			tDelay = GetTickCount();//���۽ð�
		}

		tTemp = GetTickCount();//����ð�

		if (tTemp - tDelay >= DELAY_INTERVAL)//���� �ð� - ���۽ð� = ������ �ð�
		{
			tpPtr();
			cout << "Count:" << tCount << ", tTemp:" << tTemp << "Delay:" << tDelay << endl;
			tCount++;
			tDelay = tTemp;//���۽ð� �ʱ�ȭ
		}
	}

    return 0;
}

void OnTimeDoSomething()
{
	cout << "Timer Alive!" << endl;
}
