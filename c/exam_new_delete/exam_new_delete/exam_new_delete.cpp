// exam_new_delete.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct SRectangle 
{
	int mLeft = 0;
	int mRight = 0;
	int mTop = 0;
	int mBottom = 0;

	int mArea = 0;
};


int main()
{
	int *tpA = NULL;
	
	tpA = new int();

	if (NULL != tpA)
	{
		delete tpA;//������ �Ҵ���� �޸� ����
		tpA = NULL;//������ �ּҰ� �ʱ�ȭ
	}


	SRectangle *tRectA = NULL;
	SRectangle *tRectB = NULL;

	tRectA = new SRectangle();	
	tRectB = new SRectangle();


	if (NULL != tRectA)
	{
		delete tRectA;
		tRectA = NULL;
	}

	if (NULL != tRectB)
	{
		delete tRectB;
		tRectB = NULL;
	}

    return 0;
}

