#include "Enemy.h"
#include "Arrow.h"

bool Enemy::init()
{
	if (!Actor::init())
	{
		return false;
	}


	/*auto tSeq = Sequence::create(
		MoveBy::create(0.6,Vec2(0, 10)),
		MoveBy::create(0.6, Vec2(0, -10)),
		nullptr
	);
	auto tRepeat = RepeatForever::create(tSeq);
	this->runAction(tRepeat);*/


	return true;
}

void Enemy::AddParts(EnemyParts * tParts)
{
	mParts.pushBack(tParts);
	this->addChild(tParts);
}

//Actor -> this -> mParts
//���ڷ� �Ѿ��� ������ �Ѿ˿�
//�ڽ� ������ �浹���� üũ �� ���� ����
// bool Enemy::checkCollisionBulletToParts(CBullet * tBullet)
// {
// 	if (mParts.size() > 0)
// 	{
// 		for (int i = 0; i < mParts.size(); i++)
// 		{
// 			if (mParts.at(i)->getIsAlive())
// 			{
// 				if (utils::getCascadeBoundingBox(mParts.at(i))
// 					.intersectsCircle(
// 						tBullet->getPosition(),
// 						tBullet->getSprite()->getContentSize().width * 0.5
// 					))
// 				{
// 					//log("collision");
// 					mParts.at(i)->Hit();
// 					return true;
// 				}//isCollision?
// 			}//isVisible?
// 		}//loop Parts
// 	}//Parts Count > 0
// 	return false;
// }

//void Enemy::CheckCollisionToActor(Actor * tActor)
//{
//	if (mParts.size() > 0)
//	{
//		for (int i = 0; i < mParts.size(); i++)
//		{
//
//		}
//	}
//}

bool Enemy::GetPartsAlive()
{
	if (mParts.size() > 0)
	{
		for (int i = 0; i < mParts.size(); i++)
		{
			if (mParts.at(i)->IsAlive())
			{
				return true;
			}
		}
	}

	return false;
}


void Enemy::SetAlive(bool tIsAlive)
{
	if (mParts.size() > 0)
	{
		for (int i = 0; i < mParts.size(); i++)
		{
			mParts.at(i)->SetAlive(tIsAlive);
		}
	}
}

bool Enemy::IsAlive()
{
	if (mParts.size() > 0)
	{
		for (int i = 0; i < mParts.size(); i++)
		{
			if (mParts.at(i)->IsAlive())
			{
				return true;
			}
		}
	}
	return false;
}

void Enemy::DestroyParts()
{
	//mDestroyPartsCount++;
	//log("%d", mDestroyPartsCount);

	//if (mDestroyPartsCount == 2)
	//{
	//	mParts.at(mParts.size() - 1)->setState(EnemyParts::STATE_ATTACK);
	//}
	//if (mDestroyPartsCount == 3)
	//{
	//	mParts.at(mParts.size() - 2)->setState(EnemyParts::STATE_ATTACK);
	//}
}

void Enemy::CheckCollisionArrow(Arrow * tArrow)
{
	bool result = false;
	Actor * other = nullptr;

	if (mParts.size() > 0)
	{
		for (int i = 0; i < mParts.size(); i++)
		{
			if (utils::getCascadeBoundingBox(mParts.at(i))
				.intersectsRect(utils::getCascadeBoundingBox(tArrow)))
			{
				result = true;
				other = mParts.at(i);
				break;
			}
		}
	}
	tArrow->OnCollisionOther(result, other);
}