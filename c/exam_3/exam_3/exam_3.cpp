// exam_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//����ü ����
struct SRectangle
{
	int mLeft = 0;
	int mTop = 0;
	int mRight = 0;
	int mBottom = 0;

};

int main()
{

	printf("main start\n\n");


	SRectangle tRectangle;
	/*tRectangle.mLeft = 0;
	tRectangle.mRight = 5;
	tRectangle.mTop = 0;
	tRectangle.mBottom = 5;
*/
	int tInput = 0;

	int tArea = 0;
	int tWidth = 0;
	int tHeight = 0;

	//3. while loop�� �̿��ؼ� ��� ���� �Է¹޾� �簢���� ���̸� ���
	while (1)
	{
		printf("1. Rectangle\n2. Exit\n");
		scanf_s("%d", &tInput);

		if(1 == tInput)
		{
			//2. 4���� �Է°��� �޾� ���

			printf("mLeft : ");
			scanf_s("%d", &tRectangle.mLeft);

			printf("mRight : ");
			scanf_s("%d", &tRectangle.mRight);

			printf("mTop : ");
			scanf_s("%d", &tRectangle.mTop);

			printf("mBottom :");
			scanf_s("%d", &tRectangle.mBottom);


			tWidth = tRectangle.mRight - tRectangle.mLeft;
			tHeight = tRectangle.mBottom - tRectangle.mTop;

			//�簢���� ���� = ���� * ����
			tArea = tWidth * tHeight;
			printf("\ntArea : %d\n\n", tArea);

		}
		else if (2 == tInput)
		{
			printf("���� �����Ͻðڽ��ϱ�?(1/0)\n");
			scanf_s("%d", &tInput);
			if (1 == tInput)
			{
				break;
			}
		}
	}


	
	return 0;

}

