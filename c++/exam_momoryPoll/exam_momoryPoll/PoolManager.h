#pragma once

#include <stdio.h>

#include "TaskList.h"

class PoolManager
{
private:
	static PoolManager *mpInstance;

public:
	PoolManager();
	~PoolManager();

	static PoolManager *GetInstance();

	void CreateRyu();
	void DestroyRyu();

	void DisplayAllTaskList();


	//�ʿ��� ����Ʈ���� �߰��Ѵ�.

	//CEnemy�� ����ũ�⿵�� ����Ʈ
	//static CTaskList *mpTaskEnemyList;
	//CActor�� ����ũ�⿵�� ����Ʈ
	//static CTaskList *mpTaskActorList;


	//CEnemy�� ����ũ�⿵�� ����Ʈ
	TaskList *mpTaskEnemyList;
	//CActor�� ����ũ�⿵�� ����Ʈ
	TaskList *mpTaskActorList;
};

