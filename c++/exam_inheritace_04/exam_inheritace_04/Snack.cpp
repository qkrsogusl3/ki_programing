#include "stdafx.h"
#include "Snack.h"

#include <iostream>

using namespace std;

Snack::Snack()
{
}


Snack::~Snack()
{
}

void Snack::SetPrice2()
{
	cout << "Snack : " << endl;
}

void Snack::PrintOverride(int t)
{
	Food::PrintOverride(t);
	cout << "�ڽ� Ŭ����" << t + 1 << endl;
}
