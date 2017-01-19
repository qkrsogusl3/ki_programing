#ifndef __CENEMY_H__
#define __CENEMY_H__

#include "cocos2d.h"
#include "CUnit.h"
#include "CEnemyParts.h"

using namespace cocos2d;

class CBullet;
class CActor;

class CEnemy : public CUnit
{
protected:
	Vector<CEnemyParts *> mParts;
public:
	CREATE_FUNC(CEnemy);
	virtual bool init() override;

	void addParts(CEnemyParts * tParts);
	bool checkCollisionBulletToParts(CBullet * tBullet);
	void checkCollisionToActor(CActor * tActor);
};

#endif // !__CENEMY_H__
