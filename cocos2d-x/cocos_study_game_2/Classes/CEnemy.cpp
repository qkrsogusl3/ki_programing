#include "CEnemy.h"
#include "CBullet.h"

bool CEnemy::init()
{
	if (!CUnit::init())
	{
		return false;
	}

	return true;
}

void CEnemy::addParts(CEnemyParts * tParts)
{
	mParts.pushBack(tParts);
	this->addChild(tParts);
}

//Actor -> this -> mParts
//���ڷ� �Ѿ�� ������ �Ѿ˿� 
//�ڽ� ������ �浹���� üũ �� ��� ����
bool CEnemy::checkCollisionBulletToParts(CBullet * tBullet)
{
	if (mParts.size() > 0)
	{
		for (int i = 0; i < mParts.size(); i++)
		{
			if (mParts.at(i)->isVisible())
			{
				if (utils::getCascadeBoundingBox(mParts.at(i))
					.intersectsCircle(
						tBullet->getPosition(),
						tBullet->getSprite()->getContentSize().width * 0.5
					))
				{
					//log("collision");
					mParts.at(i)->Hit();
					return true;
				}//isCollision?
			}//isVisible?
		}//loop Parts
	}//Parts Count > 0
	return false;
}

void CEnemy::checkCollisionToActor(CActor * tActor)
{
	if (mParts.size() > 0)
	{
		for (int i = 0; i < mParts.size(); i++)
		{
			Vector<CBullet *> tBullets = mParts.at(i)->getBullets();
			if (tBullets.size() > 0)
			{
				for (int j = 0; j < tBullets.size(); j++)
				{
					tBullets.at(j)->checkCollisionActor(tActor);
				}
			}
		}
	}
}



