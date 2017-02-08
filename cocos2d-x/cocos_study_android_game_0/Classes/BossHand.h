#ifndef __BOSSHAND_H__
#define __BOSSHAND_H__

#include "EnemyParts.h"


class BossHand : public EnemyParts
{
public:
	enum HandDir
	{
		HandDir_Left = -1,
		HandDir_Right = 1,
	};
private:
	Sprite * mSprite = nullptr;
	char mHandDir = 0;
	
	Vec2 mInitPos;
	
	//idle
	float mIdleRadian = 0;



public:
	CREATE_FUNC(BossHand);
	virtual bool init() override;
	virtual void update(float dt) override;
	virtual void onEnter() override;

	void InitHand(HandDir dir);
};

#endif // !__BOSSHAND_H__
