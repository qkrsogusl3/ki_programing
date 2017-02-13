// exam_momoryPoll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "TaskList.h"
#include "Enemy.h"
#include "Actor.h"
#include "PoolManager.h"

using namespace std;

int main()
{
	// insert code here...
	std::cout << "This is exam to manage memory!\n";



	cout << "size of CTask: " << sizeof(Task) << endl;
	cout << "size of CUnit: " << sizeof(Unit) << endl;
	cout << "size of CEnemy: " << sizeof(Enemy) << endl;
	cout << "size of CActor: " << sizeof(Actor) << endl;



	PoolManager::GetInstance()->CreateRyu();



	vector<Enemy *> tEnemyVec;

	Enemy *tpEnemy = NULL;


	//���⼭ new�� C++���� �����ϴ� �������� ���� �޸� �Ҵ��� ������� �ʰ�
	//��������ũ�� ����Ʈ�� �̿��� �޸𸮰����� �̿��Ѵ�.
	tpEnemy = NULL;
	tpEnemy = new Enemy(PoolManager::GetInstance()->mpTaskEnemyList);
	tpEnemy->SetX(0);
	tpEnemy->SetY(0);

	tEnemyVec.push_back(tpEnemy);

	tpEnemy = NULL;
	tpEnemy = new Enemy(PoolManager::GetInstance()->mpTaskEnemyList);
	tpEnemy->SetX(100);
	tpEnemy->SetY(0);

	tEnemyVec.push_back(tpEnemy);


	Actor *tpActor = NULL;


	//���⼭ new�� C++���� �����ϴ� �������� ���� �޸� �Ҵ��� ������� �ʰ�
	//��������ũ�� ����Ʈ�� �̿��� �޸𸮰����� �̿��Ѵ�.
	tpActor = NULL;
	tpActor = new Actor(PoolManager::GetInstance()->mpTaskActorList);
	tpActor->SetX(0);
	tpActor->SetY(0);

	//tActorVec.push_back(tpActor);




	int ti = 0;
	for (ti = 0; ti<tEnemyVec.size(); ti++)
	{
		cout << "X: " << tEnemyVec[ti]->GetX() << ", " << "Y: " << tEnemyVec[ti]->GetY() << endl;
	}

	PoolManager::GetInstance()->DisplayAllTaskList();










	if (NULL != tpActor)
	{
		delete tpActor;
		tpActor = NULL;
	}


	for (ti = 0; ti<tEnemyVec.size(); ti++)
	{
		//���⼭ delete�� C++���� �����ϴ� �������� ���� �޸� �Ҵ��� ������� �ʰ�
		//��������ũ�� ����Ʈ�� �̿��� �޸𸮰����� �̿��Ѵ�.
		if (NULL != tEnemyVec[ti])
		{
			delete tEnemyVec[ti];
			tEnemyVec[ti] = NULL;
		}
	}
	tEnemyVec.clear();

	PoolManager::GetInstance()->DisplayAllTaskList();











	PoolManager::GetInstance()->DestroyRyu();
    return 0;
}

