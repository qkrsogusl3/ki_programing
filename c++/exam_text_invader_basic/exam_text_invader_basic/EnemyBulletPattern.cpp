#include "stdafx.h"
#include "EnemyBulletPattern.h"
#include "Actor.h"

#include <iostream>

using namespace std;

CEnemyBulletPattern::CEnemyBulletPattern()
{
}


CEnemyBulletPattern::~CEnemyBulletPattern()
{
}

void CEnemyBulletPattern::Clean(char * tpPixel)
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		mBullets[ti]->Clean(tpPixel);
	}
}

void CEnemyBulletPattern::Update()
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		if (mBullets[ti]->GetAlive() == true)
		{
			mBullets[ti]->Update();
		}
	}
}

void CEnemyBulletPattern::Display(char * tpPixel)
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		if (mBullets[ti]->GetAlive() == true)
		{
			mBullets[ti]->Display(tpPixel);
		}
	}
}

void CEnemyBulletPattern::Destroy()
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		mBullets[ti]->Destroy();
	}

	delete this;
}

void CEnemyBulletPattern::SetAlive(bool tIsAlive)
{
	for (int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i]->SetAlive(tIsAlive);
	}
}

bool CEnemyBulletPattern::GetAlive()
{
	for (int i = 0; i < mBullets.size(); i++)
	{
		//���� ź�� �� �ϳ��� ����ִٸ� 
		if (mBullets[i]->GetAlive() == true)
		{
			//���� �ν��Ͻ��� ����ִٰ� �Ǵ�
			return true;
		}
	}
	//��� ź�� ���� ���¶�� ���� �ν��Ͻ��� �������¶�� �Ǵ�
	return false;
}

void CEnemyBulletPattern::SetPositionForFire(int tX, int tY)
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		mBullets[ti]->SetPositionForFire(tX, tY);
	}
}

bool CEnemyBulletPattern::DoCollisionWithActor(CActor * pPlayer)
{
	bool tResult = false;

	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		if (mBullets[ti]->GetAlive())
		{

			if (mBullets[ti]->GetX() == pPlayer->GetX() 
				&& mBullets[ti]->GetY() == pPlayer->GetY())
			{
				cout << "EnemyBullet VS actor Collision" << endl;
				tResult = true;
			}
		}
	}

	return tResult;
}

CEnemyBulletPattern & CEnemyBulletPattern::AddBullet(CEnemyBullet * tpEnemyBullet)
{
	mBullets.push_back(tpEnemyBullet);
	mBullets.back()->SetAlive(false);
	return *this;
}
