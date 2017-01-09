#include "stdafx.h"
#include "ActorBulletPattern.h"
#include "Enemy.h"

#include <iostream>

using namespace std;

CActorBulletPattern::CActorBulletPattern()
{

}


CActorBulletPattern::~CActorBulletPattern()
{

}

void CActorBulletPattern::Clean(char * tpPixel)
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		mBullets[ti]->Clean(tpPixel);
	}
}

void CActorBulletPattern::Update()
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

void CActorBulletPattern::Display(char * tpPixel)
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

void CActorBulletPattern::Destroy()
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		mBullets[ti]->Destroy();
	}

	delete this;
}

void CActorBulletPattern::SetAlive(bool tIsAlive)
{
	for (int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i]->SetAlive(tIsAlive);
	}
}

bool CActorBulletPattern::GetAlive()
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

void CActorBulletPattern::SetPositionForFire(int tX, int tY)
{
	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		mBullets[ti]->SetPositionForFire(tX, tY);
	}
}

bool CActorBulletPattern::DoCollisionWithEnemy(CEnemy * tpEnemy)
{

	bool tResult = false;

	int ti = 0;
	for (ti = 0; ti < mBullets.size(); ti++)
	{
		if (mBullets[ti]->GetAlive())
		{
			if (mBullets[ti]->GetX() == tpEnemy->GetX()
				&& mBullets[ti]->GetY() == tpEnemy->GetY())
			{
				cout << "ActorBullet VS Enemy Collision" << endl;
				tResult = true;
			}
		}
	}

	return tResult;
}

CActorBulletPattern & CActorBulletPattern::AddBullet(CActorBullet * tpEnemyBullet)
{
	mBullets.push_back(tpEnemyBullet);
	mBullets.back()->SetAlive(false);
	return *this;
}
