#include "stdafx.h"
#include "Dice.h"

#include <stdlib.h>
#include <time.h>

CDice::CDice()
{
	srand(time(NULL));//���� �õ� ����
}


CDice::~CDice()
{
}

int CDice::DoThrow(int tMaxNumber)
{
	mDiceNumber = rand() % tMaxNumber + 1;

	return mDiceNumber;
}

int CDice::GetDiceNumber()
{
	return mDiceNumber;
}
